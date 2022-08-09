#include<SDL.h>
#include<stdio.h>

#include"time.h"

struct point { double x = 0; double y = 0; };

point ship_points[] = { {-2,5}, {0,-5}, {2,5} };

#define num_elements(ar) (sizeof(ar)/sizeof(ar[0]))

void draw_points(SDL_Renderer* ren, point* pts, int num_pts)
{
	while (num_pts > 1)
	{
		SDL_RenderDrawLine(ren, pts->x, pts->y, (pts + 1)->x, (pts + 1)->y);
		--num_pts;
		++pts;
	}
}

int main(int argc, char** argv)
{
	SDL_Window*   win = SDL_CreateWindow("game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 240, SDL_WINDOW_SHOWN);
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	SDL_Event ev;

	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);
	
	// stage #1 phosphor effect
	// draw line on mouse
	int x, y;
	SDL_Rect full_screen_rect = { .x = 0, .y = 0, .w = 320, .h = 240 };

	do {
		if (delta_frames() > 0)
		{
			SDL_SetRenderDrawColor(ren, 0, 0, 0, 8);
			SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_MUL);
			SDL_RenderFillRect(ren, &full_screen_rect);

			SDL_GetMouseState(&x, &y);
			SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
			SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_NONE);
			draw_points(ren, ship_points, num_elements(ship_points));

			SDL_RenderPresent(ren);
			SDL_RenderDrawPoint(ren, x, y);
		}
		SDL_PollEvent(&ev);

	} while (ev.key.keysym.scancode != SDL_SCANCODE_ESCAPE);

	
	SDL_DestroyWindow(win);
	return 0;
}
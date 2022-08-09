// time.cpp
#include<chrono>

using namespace std::chrono;

static const int FPS    = 60;
static const double SPF = 1 / (double)FPS;

auto clk = high_resolution_clock();
auto cur_t = clk.now();
auto prev_t = clk.now();
auto dt = high_resolution_clock::duration();

double ratio = high_resolution_clock::period::num / (double)high_resolution_clock::period::den;


// in seconds
double delta_time()
{
	cur_t = clk.now();
	dt = cur_t - prev_t;
	prev_t = cur_t;
	return dt.count() * ratio;
}

double dt_acc = 0.0;

unsigned int delta_frames()
{
	unsigned int df = 0;

	dt_acc += delta_time();
	while (dt_acc > SPF)
	{
		++df;
		dt_acc -= SPF;
	}

	return df;
}
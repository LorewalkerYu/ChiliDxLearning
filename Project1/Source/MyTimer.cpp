#include "../Header/MyTimer.h"
using namespace std::chrono;
MyTimer::MyTimer()
{
	last = steady_clock::now();
}

float MyTimer::Mark()
{
	const steady_clock::time_point old = last;
	last = steady_clock::now();
	const duration<float> frameTime = last - old;
	return frameTime.count();

}

float MyTimer::Peek() const
{
	return duration<float>((steady_clock::now() - last)).count();
}

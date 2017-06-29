#include "Clock.h"
#include <Windows.h>

SYSTEMTIME before_st, after_st;

Clock::Clock()
{
	
	GetSystemTime(&before_st);
	//GetSystemTime(&after_st);

	long before_msec = (before_st.wMinute * 60 * 1000) + (before_st.wSecond * 1000) + (before_st.wMilliseconds);
	this->previous_time = before_msec;
}
long int Clock::delta(void)
{
	GetSystemTime(&after_st);
	long after_msec = (after_st.wMinute * 60 * 1000) + (after_st.wSecond * 1000) + (after_st.wMilliseconds);
	long delta =  after_msec - this->previous_time;
	this->previous_time = after_msec;   // set the previous time to 0;
	return delta;
}
long int Clock::split(void) const
{
	GetSystemTime(&after_st);
	long after_msec = (after_st.wMinute * 60 * 1000) + (after_st.wSecond * 1000) + (after_st.wMilliseconds);
	long split = after_msec - this->previous_time;
	return split;
}
Clock::~Clock()
{
}

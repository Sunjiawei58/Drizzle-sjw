#include "s_EventStep.h"
using namespace df;

s_EventStep::s_EventStep()
{
}

s_EventStep::s_EventStep(int init_step_count)
{
	step_count = init_step_count;
}

void s_EventStep::setStepCount(int new_step_count)
{
	step_count = new_step_count;
}
int s_EventStep::getStepCount() const
{
	return step_count;
}
s_EventStep::~s_EventStep()
{
}


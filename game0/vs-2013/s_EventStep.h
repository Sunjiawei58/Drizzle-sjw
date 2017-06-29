#ifndef _S_EVENTSTEP_H_
#define _S_EVENTSTEP_H_
#include "s_Event.h"

namespace df
{

	const std::string STEP_EVENT = "df::step";
	class s_EventStep :public s_Event
	{
	private:
		int step_count;
	public:
		s_EventStep();
		s_EventStep(int init_step_count);
		void setStepCount(int step_count);
		int getStepCount() const;
		~s_EventStep();
	};
}
#endif;
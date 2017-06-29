#include "s_Event.h"
using namespace df;

s_Event::s_Event()
{

}


s_Event::~s_Event()
{
}

void s_Event::setType(std::string type)
{
	event_type = type;
}
std::string s_Event::getType() const
{
	return event_type;
}
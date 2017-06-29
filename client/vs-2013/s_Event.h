#pragma once
#ifndef _S_EVENT_H_
#define _S_EVENT_H_

#include <string>
namespace df
{


	class s_Event
	{
	private:
		std::string event_type;
	public:
		s_Event();
		virtual ~s_Event();
		void setType(std::string type);
		std::string getType() const;
	};
}
#endif

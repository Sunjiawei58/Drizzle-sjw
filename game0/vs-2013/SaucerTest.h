#pragma once

#include "s_Object.h"
#include "s_Event.h"
class SaucerTest:  public df::s_Object
{
public:
	int hp;
	SaucerTest();
	~SaucerTest();
	virtual SaucerTest* clone() const;
	virtual int eventHandler(const df::s_Event *p_e);
};


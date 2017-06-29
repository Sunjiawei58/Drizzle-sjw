#pragma once
#include "s_Object.h"
#include "Position.h"
class bullet :	public df::s_Object
{
public:
	bullet();
	bullet(df::Position pos);
	~bullet();
	int eventHandler(const df::s_Event *p);
	bullet * clone() const;
	int out();
};


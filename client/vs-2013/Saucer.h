#pragma once
#include "s_Object.h"
class Saucer : public df::s_Object
{
private:
	int hp = 0;
public:
	int eventHander(const df::s_Event *p);
	void out();
	void moveToStart();
	Saucer * clone() const;
	Saucer();
	~Saucer();
};

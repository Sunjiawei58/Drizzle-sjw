#pragma once
#include "s_Object.h"
class GameOver :
	public df::s_Object
{
public:
	GameOver();
	~GameOver();
	int eventHandler(const df::s_Event *p);
	GameOver * clone() const;

};


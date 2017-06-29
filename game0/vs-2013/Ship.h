#pragma once
#include "s_Object.h"
class Ship: public df::s_Object
{
private:
	
	int hp;
	int missMax;
	int score;
public:
	Ship();
	//static Ship& getInstance();
	~Ship();
	int eventHandler(const df::s_Event *p);
	Ship * clone() const;

	int getScore();
	void addScore();
	void missSaucer();
	int getMiss();
};


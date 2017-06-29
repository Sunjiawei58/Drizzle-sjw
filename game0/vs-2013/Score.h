#pragma once
#include "s_Object.h"
class Score :
	public df::s_Object
{
private:
	 int score;
public:
	void addScore();
	int getScore();
	Score();
	~Score();
	int eventHandler(const df::s_Event *p);
	Score * clone() const;
	void draw();
};


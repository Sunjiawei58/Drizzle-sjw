#include "Score.h"
#include "s_GraphicsManager.h"


void Score::addScore()
{
	++score;
}

int Score::getScore()
{
	return score;
}

Score::Score()
{
	score = 0;
}


Score::~Score()
{
}

int Score::eventHandler(const df::s_Event * p)
{
	return 0;
}

Score * Score::clone() const
{
	return new Score(*this);
}

void Score::draw()
{
	std::string score_content = "Score is ";
	score_content.append(std::to_string(score));
	df::s_GraphicsManager::getInstance().drawString(df::Position(0, 0), score_content, df::RIGHT_JUSTIFIED, df::WHITE);
}

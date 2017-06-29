#include "Position.h"
using namespace df;
Position::Position(int x, int y)
{
	this->x = x;
	this->y = y;
}
Position::Position()
{
	this->x = 0;
	this->y = 0;   ///default position is (0,0)
}
int Position::getX() const
{
	return this->x;
}
int Position::getY() const
{
	return this->y;
}
void Position::setX(int x)
{
	this->x = x;
}
void Position::setY(int y)
{
	this->y = y;
}
void Position::setXY(int x, int y)
{
	this->x = x;
	this->y = y;
}
bool Position::operator==(const Position &other) const
{
	if (other.getX() == this->getX() && other.getY() == this->getY())
	{
		return true;
	}
	else return false;
}
bool Position::operator!=(const Position &other) const
{
	if (this->operator==(other))
	{
		return false;
	}
	else return true;
}
#include "s_Box.h"
using namespace df;

s_Box::s_Box()
{
	horizontal = 1;
	vertical = 1;
}


s_Box::~s_Box()
{
}

s_Box::s_Box(Position init_corner, int init_horizontal, int init_vertical)
{
	corner = init_corner;
	horizontal = init_horizontal;
	vertical = init_vertical;
}

void s_Box::setCorner(Position new_corner)
{
	corner = new_corner;
}
Position s_Box::getCorner() const
{
	return corner;
}
void s_Box::setHorizontal(int new_horizontal)
{
	horizontal = new_horizontal;
}
int s_Box::getHorizontal()const
{
	return horizontal;
}

void s_Box::setVertical(int new_vertical)
{
	vertical = new_vertical;
}
int s_Box::getVertical()const
{
	return vertical;
}
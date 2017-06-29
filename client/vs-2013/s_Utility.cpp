#include "s_Utility.h"
#include "s_WorldManager.h"
using namespace df;

s_Utility::s_Utility()
{
}


s_Utility::~s_Utility()
{
}

bool s_Utility::positionIntersect(Position p1, Position p2)
{
	if (p1.getX() == p2.getY()  &&  p1.getY() == p2.getY())
	{
		return true;
	}
	else return false;
}
bool s_Utility::boxIntersectsBox(s_Box A, s_Box B)
{
	bool x_overlap;
	bool y_overlap;
	int Ax1, Ax2, Bx1, Bx2;
	int Ay1, Ay2, By1, By2;
	Ax1 = A.getCorner().getX();
	Ax2 = A.getCorner().getX()+A.getHorizontal();
	Bx1 = B.getCorner().getX();
	Bx2 = B.getCorner().getX()+B.getHorizontal();

	Ay1 = A.getCorner().getY();
	Ay2 = A.getCorner().getY()+A.getVertical();
	By1 = B.getCorner().getY();
	By2 = B.getCorner().getY()+B.getVertical();
	if ((Bx1<=Ax1 && Ax1<=Bx2) || (Ax1<=Bx1 && Bx1<=Ax2))
	{
		//Bx1 <= Ax1 <=Bx2 || Ax1<=Bx1<=Ax2
		x_overlap = true;
	}
	if ((By1 <= Ay1 && Ay1 <= By2) || (Ay1 <= By1 && By1 <= Ay2))
	{
		//same for the vertical direction.
		y_overlap = true;
	}

	if (x_overlap && y_overlap)
	{
		return true;
	}
	else
	{
		return false;
	}
}

s_Box s_Utility::getWorldBox(const s_Object *p_o)
{
	s_Box temp_box = p_o->getBox();
	temp_box = getWorldBox(p_o, p_o->getPosition());
	return temp_box;
}
s_Box s_Utility::getWorldBox(const s_Object *p_o, Position location)
{
	//don't really understand why it exist.
	s_Box temp_box = p_o->getBox();
	Position corner = temp_box.getCorner();
	corner.setX(corner.getX() + location.getX());
	corner.setY(corner.getY() + location.getY());
	temp_box.setCorner(corner);
	return temp_box;
	
}
Position s_Utility::worldToView(Position world_pos)
{
	Position view_origin = s_WorldManager::getInstance().getView().getCorner();
	int view_x = view_origin.getX();
	int view_y = view_origin.getY();
	Position view_pos(world_pos.getX() - view_x, world_pos.getY() - view_y);
	return view_pos;

}
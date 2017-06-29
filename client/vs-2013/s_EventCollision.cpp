#include "s_EventCollision.h"
#include "s_Object.h"
using namespace df;

s_EventCollision::s_EventCollision()
{
	this->setType(S_COLLISION_EVENT);
}


s_EventCollision::s_EventCollision(s_Object *p_o1, s_Object *p_o2, Position p)
{
	this->setType(S_COLLISION_EVENT);
	p_obj1 = p_o1;
	p_obj2 = p_o2;
	pos = p;
}

void s_EventCollision::setObject1(s_Object *p_new_o1)
{
	p_obj1 = p_new_o1;
}

s_Object *s_EventCollision::getObject1() const
{
	return p_obj1;
}

void s_EventCollision::setObject2(s_Object *p_new_o2)
{
	p_obj2 = p_new_o2;
}

s_Object *s_EventCollision::getObject2() const
{
	return p_obj2;
}

void s_EventCollision::setPosition(Position new_pos)
{
	pos = new_pos;
}

Position s_EventCollision::getPosition() const
{
	return pos;
}
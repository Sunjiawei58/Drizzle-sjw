#ifndef S_COLLISION_EVENT_H
#define S_COLLISION_EVENT_H
#include "s_Event.h"
#include "s_Object.h"
namespace df
{

	const std::string S_COLLISION_EVENT = "df::collision";
class s_EventCollision :	public s_Event
{
private:
	Position pos;
	s_Object *p_obj1;
	s_Object *p_obj2;
public:

	s_EventCollision();

	s_EventCollision(s_Object *p_o1, s_Object *p_o2, Position p);

	void setObject1(s_Object *p_new_o1);

	s_Object *getObject1() const;

	void setObject2(s_Object *p_new_o2);

	s_Object *getObject2() const;

	void setPosition(Position new_pos);

	Position getPosition() const;
};
}
#endif;

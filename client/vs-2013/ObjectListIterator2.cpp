#include "ObjectListIterator2.h"
#include "ObjectList2.h"
using namespace df;

ObjectListIterator2::ObjectListIterator2()
{

}
ObjectListIterator2::ObjectListIterator2(const ObjectList2 *p_l)
{
	p_list = p_l; 
	first();
}
void ObjectListIterator2::first()
{
	index = 0;
}
void ObjectListIterator2::next()
{
	if (index < p_list->count)
	index++;
}
bool ObjectListIterator2::isDone() const
{
	return(index == p_list->count);
}
s_Object* ObjectListIterator2::currentObject() const
{
	return (p_list->list[index]);
}
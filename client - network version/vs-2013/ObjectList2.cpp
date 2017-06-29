#include "ObjectList2.h"
using namespace df;


ObjectList2::ObjectList2()
{
	count = 0;
}

bool ObjectList2::insert(s_Object *p_o)
{
	if (!isFull())
	{
		list[count] = p_o;   // index starts from 0;
		count++;
		return true;
	}
	else return false;
}
bool ObjectList2::remove(s_Object *p_o)
{
	for (int i = 0; i < count; i++)
	{
		if (list[i] == p_o)
		{
			for (int j = i; j < count - 1; j++)
			{
				list[j] = list[j + 1];
			}
			count--;
			return true;//found it
		}
		
	}
	 return false;  // cannot find it.
}
void ObjectList2::clear()
{
	count = 0;  // need to remove the storing memory; or maybe not.
}
int ObjectList2::getCount() const
{
	return this->count;
}
bool ObjectList2::isFull() const
{
	return this->count == MAX_OBJECTS ? true:false;
}
bool ObjectList2::isEmpty() const
{
	return this->count == 0 ? true : false;
}
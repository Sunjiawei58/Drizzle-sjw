
#ifndef _OBJECT2_H_
#define _OBJECT2_H_

const int MAX_OBJECTS = 5000;
#include "s_Object.h"
#include "ObjectListIterator2.h"   //which need to be writen later.
//#include <list>
namespace df
{
	class s_Object;
	class ObjectListIterator2;

	class ObjectList2
	{
	private:
		int count;
		s_Object *list[MAX_OBJECTS];
	//	std::list<Object *> list;   ///consider as stl list
	public:
		friend class ObjectListIterator2;

		ObjectList2();

		bool insert(s_Object *p_o);   // add is more appropriate (just insert into the last one.)

		bool remove(s_Object *p_o);

		void clear();

		int getCount() const;
		
		bool isEmpty() const;

		bool isFull()  const;

	};
}
#endif

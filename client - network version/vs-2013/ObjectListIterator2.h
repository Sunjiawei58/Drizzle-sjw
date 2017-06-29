
#ifndef _OBJECTLISTITERATOR_H_
#define _OBJECTLISTITERATOR_H_

#include "s_Object.h"
#include "ObjectList2.h"


namespace df{
	class s_Object;
	class ObjectList2;

	class ObjectListIterator2
	{
	private:
		ObjectListIterator2();
		int index;
		const ObjectList2 *p_list;
	public:
		ObjectListIterator2(const ObjectList2 *p_l);  //create iterator, over indicated list?

		void first();
		void next();
		bool isDone() const;

		s_Object *currentObject() const; // return pointer of the current Object, NULL if done/empty


		
	};
}
#endif

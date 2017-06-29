#ifndef S_UTILITY_H
#define S_UTILITY_H
#include "Position.h"
#include "s_Box.h"
#include "s_Object.h"
#include "ObjectList2.h"
namespace df
{
	namespace collision{

	

	}
	
	class s_Utility
	{
	public:
		static bool positionIntersect(Position p1, Position p2);
		static bool boxIntersectsBox(s_Box boxA, s_Box boxB);
		static s_Box getWorldBox(const s_Object *p_o);
		static s_Box getWorldBox(const s_Object *p_o, Position location);
		static Position worldToView(Position world_pos);
		s_Utility();
		~s_Utility();
		

	};
}
#endif;

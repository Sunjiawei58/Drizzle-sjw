#ifndef S_BOX_H
#define S_BOX_H
#include "Position.h"
namespace df
{


	class s_Box
	{
	private:
		Position corner;   // uper left corner
		int horizontal;
		int vertical;
	public:
		s_Box();
		s_Box(Position init_corner, int init_horizontal, int init_vertical);
		
		void setCorner(Position new_corner);
		Position getCorner() const;
		void setHorizontal(int new_horizontal);
		int getHorizontal()const;

		void setVertical(int new_vertical);
		int getVertical()	const;

		~s_Box();
	};
}

#endif;
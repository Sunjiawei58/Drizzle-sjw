#ifndef S_SPRITE_H
#define S_SPRITE_H

#include "s_Color.h"   // color
#include "s_Frame.h"
#include <string>
#include <vector>
namespace df
{


	class s_Sprite
	{
	private:
		int width;
		int height;
		int max_frame_count;
		int frame_count;
		s_Color color;
	//	s_Frame *frame;   // consider to use vector   
		std::vector<s_Frame> frame;
		std::string label;
		s_Sprite();   // why?  enresolved external symbol
	public:
		s_Sprite(int max_frames);
		void setWidth(int new_width);
		int getWidth() const;

		void setHeight(int new_height);
		int getHeight() const;

		void setColor(s_Color new_color);
		s_Color getColor() const;

		int getFrameCount() const;

		int addFrame(s_Frame new_frame);
		
		//get next sprite frame indicated by number
		//return empty frame if out if range [0, frame_count]
		s_Frame getFrame(int frame_number);
		void setLabel(std::string new_label);
		std::string getLabel() const;
		~s_Sprite();
	};
}
#endif;
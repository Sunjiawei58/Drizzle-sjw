#include "s_Sprite.h"
#include <vector>
#include "s_ResourceManager.h"
using namespace df;
s_Sprite::s_Sprite()
{

}


s_Sprite::~s_Sprite()
{
	if (frame.size()!=0)
	{
		delete &frame;     // how to delete the array?
	}
}

s_Sprite::s_Sprite(int max_frames)
{
	//default
	frame_count = 0;
	width = 0;
	height = 0;
	//s_Frame[max_frames];   // how to declare the array?
	frame.reserve(max_frames);
	max_frame_count = max_frames;
	color = S_COLOR_DEFAULT;
	s_ResourceManager& resource_manager = s_ResourceManager::getInstance();
	resource_manager.insertSprite(this);
}
void s_Sprite::setWidth(int new_width)
{
	width = new_width;
}
int s_Sprite::getWidth() const
{
	return width;
}

void s_Sprite::setHeight(int new_height)
{
	height = new_height;
}
int s_Sprite::getHeight() const
{
	return height;
}

void s_Sprite::setColor(s_Color new_color)
{
	color = new_color;
}
s_Color s_Sprite::getColor() const
{
	return color;
}

int s_Sprite::getFrameCount() const
{
	return frame_count;
}

int s_Sprite::addFrame(s_Frame new_frame)
{
	if (frame_count == max_frame_count)
	{
		return -1; // for fill error.
	}
	else
	{
		frame.push_back(new_frame);
//		frame[frame_count] = new_frame;
		frame_count++;
			return 1; // for ok
	}
}

//get next sprite frame indicated by number
//return empty frame if out if range [0, frame_count]
s_Frame s_Sprite::getFrame(int frame_number)
{
	if (frame_number<0 || frame_number > max_frame_count)
	{
		s_Frame *empty_frame = new s_Frame();
		return *empty_frame;
	}

	return frame[frame_number];
}

void s_Sprite::setLabel(std::string new_label)
{
	label = new_label;
}
std::string s_Sprite::getLabel() const
{
	return label;
}
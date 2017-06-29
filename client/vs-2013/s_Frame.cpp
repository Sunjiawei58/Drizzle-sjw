#include "s_Frame.h"

using namespace df;
s_Frame::s_Frame()
{
	width = 0;
	height = 0;
	frame_str = "";
}


s_Frame::s_Frame(int width, int height, std::string frame_str)
{
	width = width;
	height = height;
	frame_str = frame_str;

}
int s_Frame::getWidth() const
{
	return width;
}

void s_Frame::setWidth(int new_width)
{
	width = new_width;
}

int s_Frame::getHeight() const
{
	return height;
}

void s_Frame::setHeight(int new_height)
{
	height = new_height;
}

void s_Frame::setString(std::string new_str)
{
	frame_str = new_str;
}

std::string s_Frame::getString() const
{
	return frame_str;
}
bool s_Frame::isEmpty()
{
	if (frame_str.compare("") == 0)
	{
		return true;
	}
	else return false;
}
s_Frame::~s_Frame()
{

}
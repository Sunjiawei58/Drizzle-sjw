#ifndef S_FRAME_H
#define S_FRAME_H
#include <string>
namespace df
{


	class s_Frame
	{
	private:
		int width;
		int height;
		std::string frame_str;
	public:
		s_Frame();
		s_Frame(int width,int height, std::string frame_str);
		~s_Frame();

		int getWidth() const;

		void setWidth(int new_width);

		int getHeight() const;

		void setHeight(int new_height);

		void setString(std::string new_str);

		std::string getString() const;

		bool isEmpty();
	};

}
#endif
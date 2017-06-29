#ifndef _S_GRAPHICS_MANAGER_H
#define _S_GRAPHICS_MANAGER_H
#include "s_Manager.h"
#include <SFML/Graphics.hpp>
#include "Position.h"
#include "s_Color.h"
#include "s_Frame.h"
namespace df{

	const int WINDOW_HORIZONTAL_PIXELS_DEFAULT = 1024;
	const int WINDOW_VERTICAL_PIXELS_DEFAULT = 768;
	const int WINDOW_HORIZONTAL_CHARS_DEFAULT = 80;
	const int WINDOW_VERTICAL_CHARS_DEFAULT = 24;
	const int WINDOW_STYLE_DEFUALT = sf::Style::Titlebar;
	const sf::Color WINDOW_BACKGROUND_COLOR_DEFAULT = sf::Color::Black;
	const std::string WINDOW_TITLE_DEFAULT = "DragonFly";
	const std::string FONT_FILE_DEFAULT = "df-font.ttf";

	enum Justification{
		LEFT_JUSTIFIED,
		CENTER_JUSTIFIED,
		RIGHT_JUSTIFIED,

	};



	class s_GraphicsManager : public s_Manager
	{
		//using s_Manager::startUp; // Remove warning about hidden virtual function.  ?
	private:
		s_GraphicsManager();
		s_GraphicsManager(s_GraphicsManager const&);   // don't allow copy;
		void operator=(s_GraphicsManager const&);     //don't allow assignment
		sf::Font font;
		sf::RenderWindow *p_window;
		int window_horizontal_pixels;
		int window_vertical_pixels;
		int window_horinzontal_chars;
		int window_vertical_chars;
	public:
		static s_GraphicsManager& getInstance();
		//Open graphics window ready for text-based display
		//return 1 for ok, 0 for other;
		int startUp();
	
		void shutDown();

		int drawCh(Position world_pos, char ch, s_Color color) const;

		int getHorizontal() const;
		
		int getVertical() const;

		int getHorizontalPixels() const;

		int getVerticalPixels() const;

		int swapBuffers(int i);

		int drawString(Position pos, std::string str, Justification just, s_Color color) const;

		sf::RenderWindow *getWindow(void) const;

		int drawFrame(Position world_pos, s_Frame frame,bool sprite_centered,s_Color color);

		float s_charHeight() const;
		float s_charWidth() const;

		Position s_spacesToPixels(Position spaces) const;
		Position s_pixelsToSpaces(Position pixels) const;      // add these functiosn into member funtion?
		int screenshot(int i);

	
	};


}
#endif;



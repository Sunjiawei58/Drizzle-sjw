#include "s_GraphicsManager.h"
#include "Logmanager2.h"
#include "s_NetworkManager.h"
#include <windows.h>
#include <sstream>
using namespace df;

float s_GraphicsManager::s_charHeight() const
{
//	LogManager2::getInstance().writeLog("enter charHeight");

//	LogManager2::getInstance().writeLog("%d", getVerticalPixels());

//	LogManager2::getInstance().writeLog("%d", getVertical());

	float res = getVerticalPixels() / getVertical();
//	LogManager2::getInstance().writeLog("%f", res);
	return res;
}
float s_GraphicsManager::s_charWidth() const
{

	float res = getHorizontalPixels() / getHorizontal();
	return res;
}

Position s_GraphicsManager::s_spacesToPixels(Position spaces) const
{
	Position *resP = new Position(spaces.getX() * (int)s_charWidth(), spaces.getY() * (int)s_charHeight());

	return *resP;

}
Position s_GraphicsManager::s_pixelsToSpaces(Position pixels) const
{
	Position * resP = new Position(pixels.getX() / (int)s_charWidth(), pixels.getY() /(int) s_charHeight());
	LogManager2::getInstance().writeLog("pixelsToSpaces:%d", pixels.getX() /(int) s_charWidth());
	return *resP;

}


s_GraphicsManager::s_GraphicsManager()
{
	window_horinzontal_chars = WINDOW_HORIZONTAL_CHARS_DEFAULT;
	window_vertical_chars = WINDOW_VERTICAL_CHARS_DEFAULT;
	window_horizontal_pixels = WINDOW_HORIZONTAL_PIXELS_DEFAULT;
	window_vertical_pixels = WINDOW_VERTICAL_PIXELS_DEFAULT;

	p_window = NULL;
}


s_GraphicsManager& s_GraphicsManager::getInstance()
{
	static s_GraphicsManager *graphicsManager = NULL;
	if (!graphicsManager)
	{
		graphicsManager = new s_GraphicsManager;
	}
	return *graphicsManager;
}
int s_GraphicsManager::startUp()   
{
	LogManager2 &log_manager = LogManager2::getInstance();
 	if (p_window!=NULL)
 	{
 		return 0;
 	}
	p_window =new sf::RenderWindow (sf::VideoMode(WINDOW_HORIZONTAL_PIXELS_DEFAULT, WINDOW_VERTICAL_PIXELS_DEFAULT), "Title-DragonFly", sf::Style::Titlebar);
	p_window->setMouseCursorVisible(false);
	p_window->setVerticalSyncEnabled(true);   // ? what is ?


	//load font

	//sf::Font font;
	if (font.loadFromFile(FONT_FILE_DEFAULT) == false)
	{
		LogManager2::getInstance().writeLog("Error! Unable to load font\n");
		return 0;
	}
	sf::Text text;
	text.setFont(font);
	text.setString("Hello, Welcome to the Drizzle Demo");
	text.setCharacterSize(32);   //in pixels;
	text.setColor(sf::Color::Green);
	text.setStyle(sf::Text::Bold);
	text.setPosition(96, 134);  // in pixels;

	p_window->draw(text);
	
	//p_window->clear();
	p_window->display();
	Sleep(1000);
	log_manager.writeLog("has started the graphicsManager...");

	p_window->clear();   // first clear the display 
	s_Manager::startUp();
	return 1;                     // is success depends on the signal or the sequence of the orders?
}
void s_GraphicsManager::shutDown()
{
	delete this->p_window;
	
}
int s_GraphicsManager::drawCh(Position world_pos, char ch, s_Color color) const
{
	Position view_pos = s_Utility::worldToView(world_pos);
	if (!p_window)
	{
		return 0;
	}

	Position pixels_pos = s_spacesToPixels(view_pos);

	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(s_charWidth(), s_charHeight() - 1));
	rectangle.setFillColor(sf::Color::Black);
	rectangle.setPosition((int)pixels_pos.getX() + s_charWidth() / 2 - 5, (int)pixels_pos.getY() + s_charHeight() / 2 - 12); 
	p_window->draw(rectangle);  // stack over flow? 


/*	sf::Text testT;
	testT.setFont(this->font);
	testT.setColor(sf::Color::Red);
	testT.setCharacterSize(32);
	testT.setString("t");
	testT.setStyle(sf::Text::Bold);
	testT.setPosition(pixels_pos.getX(), pixels_pos.getY());
	p_window->draw(testT);*/
	

	static sf::Text text("", this->font);
	text.setString(ch);
	text.setStyle(sf::Text::Bold);
	LogManager2::getInstance().writeLog("ch:%c width:%f height: %f",ch,s_charWidth(),s_charHeight());
	//scale to right size
	if (s_charWidth() < s_charHeight())
	{
		text.setCharacterSize((int)s_charWidth() * 2);
		
	}
	else text.setCharacterSize((int)s_charHeight() * 2);

	//set color
	switch (color)
	{
	case BLACK:
		text.setColor(sf::Color::Black); break;
	case RED:
		text.setColor(sf::Color::Red); break;
	case GREEN:
		text.setColor(sf::Color::Green); break;
	case YELLOW:
		text.setColor(sf::Color::Yellow); break;
	case BLUE:
		text.setColor(sf::Color::Blue); break;
	case MAGENTA:
		text.setColor(sf::Color::Magenta); break;
	case CYAN:
		text.setColor(sf::Color::Cyan); break;
	case WHITE:
		text.setColor(sf::Color::White); 
		break;
	}

	text.setPosition(pixels_pos.getX(), pixels_pos.getY());
	LogManager2::getInstance().writeLog("%d,%d", pixels_pos.getX(), pixels_pos.getY());
	p_window->draw(text);
	LogManager2::getInstance().writeLog("drawCh function ended..");

	
	//p_window->display();   // i added it

	
}
int s_GraphicsManager::swapBuffers(int i)
{
	if (p_window == NULL)
	{
		return 0;   // 0 for the failure
	}
	
	p_window->display();
	screenshot(i);
	p_window->clear();
	
	LogManager2::getInstance().writeLog("swapBuffers");

	return 1;    // 1 for success;
}

int s_GraphicsManager::drawString(Position pos, std::string str, Justification just, s_Color color) const
{
	Position starting_pos = pos;
	switch (just)
	{
	case CENTER_JUSTIFIED:
		starting_pos.setX(pos.getX() - str.size() / 2);
		break;
	case LEFT_JUSTIFIED:
		starting_pos.setX(pos.getX() - str.size());
		break;
	case RIGHT_JUSTIFIED:
		break;
	}
	
	for (int i = 0; i < str.size(); i++)
	{
		Position tem_pos(starting_pos.getX() + i, starting_pos.getY());
		drawCh(tem_pos, str[i], color);
	}
	return 1;   // 1 for ok
}

int s_GraphicsManager::drawFrame(Position world_pos, s_Frame frame,bool sprite_centered,s_Color color)
{
	int x_offset;
	int y_offset;
	if (frame.isEmpty())
	{
		return -1;  // frame is empty
	}
	
	if (sprite_centered)
	{
		 x_offset = frame.getWidth() / 2;
		 y_offset = frame.getHeight() / 2;
	}
	else
	{
		x_offset = 0;
		y_offset = 0;
	}

	std::string str = frame.getString();

	for (int y = 0; y < frame.getHeight(); y++)
	{
		for (int x = 0; x < frame.getWidth(); x++)
		{
			Position tmp_pos(world_pos.getX() - x_offset + x, world_pos.getY() - y_offset + y);

			drawCh(tmp_pos, str[y*frame.getWidth() + x], color);
			
			
		}
	}
}

int s_GraphicsManager::getHorizontal() const
{
	return WINDOW_HORIZONTAL_CHARS_DEFAULT;
	//return window_horinzontal_chars;
}

int s_GraphicsManager::getVertical() const
{
	return WINDOW_VERTICAL_CHARS_DEFAULT;
//	return window_vertical_chars;
}

int s_GraphicsManager::getHorizontalPixels() const
{
	return WINDOW_HORIZONTAL_PIXELS_DEFAULT;
//	return window_horizontal_pixels;
}

int s_GraphicsManager::getVerticalPixels() const
{
	return WINDOW_VERTICAL_PIXELS_DEFAULT;
//	return window_vertical_pixels;
}
int df::s_GraphicsManager::screenshot(int i)
{
	sf::Image screenshot = p_window->capture();
	std::stringstream filename;
	filename << "screenshots2/" << i << ".jpg";

	int result=	screenshot.saveToFile(filename.str());
	//int result = screenshot.saveToFile("screenshots/1.jpg");
	return 0;
}

sf::RenderWindow *s_GraphicsManager::getWindow(void) const
{
	return p_window;
}


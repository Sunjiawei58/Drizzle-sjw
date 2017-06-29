#include "s_InputManager.h"
#include "s_GraphicsManager.h"
#include "s_WorldManager.h"

using namespace df;
s_InputManager::s_InputManager()
{
}

s_InputManager & s_InputManager::getInstance()
{
	static s_InputManager *input_manager = NULL;

	if (input_manager == NULL)
	{
		input_manager = new s_InputManager;


	}
	return *input_manager;
}

int s_InputManager::startUp()
{
	if (!s_GraphicsManager::getInstance().isStarted())
	{
		return 0;   // error
	}
	else
	{
		p_window = s_GraphicsManager::getInstance().getWindow();    // this place don;t really understand
		p_window->setKeyRepeatEnabled(false);
		s_Manager::startUp();
	}
	return 1;
}
void s_InputManager::shutDown()
{
	s_Manager::shutDown();
}

void s_InputManager::getInput()   /**--need to add some new event classes --**/
{
	sf::Event event;
	while (p_window->pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			s_Event *p_event = new s_Event();
			p_event->setType("KeyPressed");
			s_WorldManager::getInstance().onEvent(p_event);
		
		}

		if (event.type == sf::Event::KeyReleased)
		{
			s_Event *p_event = new s_Event();
			p_event->setType("KeyRelease");
			s_WorldManager::getInstance().onEvent(p_event);
		}

		if (event.type == sf::Event::MouseMoved)
		{
			s_Event *p_event = new s_Event();
			p_event->setType("MouseMoved");
			s_WorldManager::getInstance().onEvent(p_event);
		}
			// don't have mouse clicked?
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		s_Event *p_event = new s_Event();
		p_event->setType("Keyboard_UP");
		s_WorldManager::getInstance().onEvent(p_event);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		s_Event *p_event = new s_Event();
		p_event->setType("Keyboard_Down");
		s_WorldManager::getInstance().onEvent(p_event);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		s_Event *p_event = new s_Event();
		p_event->setType("Keyboard_Left");
		s_WorldManager::getInstance().onEvent(p_event);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		s_Event *p_event = new s_Event();
		p_event->setType("Keyboard_Right");
		s_WorldManager::getInstance().onEvent(p_event);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		s_Event *p_event = new s_Event();
		p_event->setType("Mouse_Left");
		s_WorldManager::getInstance().onEvent(p_event);
	}
}
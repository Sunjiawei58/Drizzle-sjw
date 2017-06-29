#include "s_InputManager.h"
#include "s_GraphicsManager.h"
#include "s_WorldManager.h"
#include "Logmanager2.h"
#include "s_NetworkManager.h"

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
		p_window = s_GraphicsManager::getInstance().getWindow();    // 
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
	bool hasEvent = false;
	noEvent noEve;
	while (p_window->pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			hasEvent = true;
			s_EventKeyBoard *p_eventKey = new s_EventKeyBoard();
			
			p_eventKey->setKey ((Input::Key)event.key.code);
			p_eventKey->setKeyboardAction(KEY_PRESSED);
			//s_Event *p_event = new s_Event();
			p_eventKey->setType("KeyPressed");
			LogManager2::getInstance().writeLog("there should be an event down...%d", p_eventKey->getKey());
			
			commandPakcetKey cpk;
			//	cpk.type = "KeyPressed";
			cpk.keyboard_action = p_eventKey->getKeyboardAction();   // this is keydown condition not the press
			cpk.keyborad_value = (Input::Key)event.key.code;
			
			cpk.hasEvent = true;
			cpk.len = sizeof(cpk);
			cpk.timeCounter = s_WorldManager::getInstance().getTimeCounter();
			LogManager2::getInstance().writeLog("the time counter is %d", cpk.timeCounter);
			//Sleep(100);
			  // simulate for the lag of 100ms.
			s_NetworkManager::getInstance().df_send(static_cast<commandPakcetKey *>(&cpk), cpk.len);
			
		
		
		}

		if (event.type == sf::Event::KeyReleased)
		{
			hasEvent = true;
			s_Event *p_event = new s_Event();
			p_event->setType("KeyRelease");
			s_WorldManager::getInstance().onEvent(p_event);
		}

		if (event.type == sf::Event::MouseMoved)
		{
			//hasEvent = true;
			s_Event *p_event = new s_Event();
			p_event->setType("MouseMoved");
			s_WorldManager::getInstance().onEvent(p_event);
		}
			// don't have mouse clicked?
		
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		hasEvent = true;
		s_EventKeyBoard *p_kevent = new s_EventKeyBoard();
		p_kevent->setKey(Input::UpArrow);
		p_kevent->setKeyboardAction(KEY_DOWN);
		
		s_WorldManager::getInstance().onEvent(p_kevent);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		hasEvent = true;
		s_EventKeyBoard *p_kevent = new s_EventKeyBoard();
		p_kevent->setKey(Input::DownArrow);
		p_kevent->setKeyboardAction(KEY_DOWN);
		//LogManager2::getInstance().writeLog("there should be an event down...%d",);
		//s_WorldManager::getInstance().onEvent(p_kevent);
		// network sending the command message
		
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		hasEvent = true;
		s_EventKeyBoard *p_kevent = new s_EventKeyBoard();
		p_kevent->setKey(Input::LeftArrow);
		p_kevent->setKeyboardAction(KEY_DOWN);
		s_WorldManager::getInstance().onEvent(p_kevent);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		hasEvent = true;
		s_EventKeyBoard *p_kevent = new s_EventKeyBoard();
		p_kevent->setKey(Input::RightArrow);
		p_kevent->setKeyboardAction(KEY_DOWN);
		s_WorldManager::getInstance().onEvent(p_kevent);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		hasEvent = true;
		s_Event *p_event = new s_Event();
		p_event->setType("Mouse_Left");
		s_WorldManager::getInstance().onEvent(p_event);
	}
// 	if(!hasEvent)  // event cannot be recognized
// 	{
// 		commandPakcetKey cpk;
// 		cpk.keyboard_action = UNDEFINED_KEYBOARD_ACTION;
// 		cpk.keyborad_value = (Input::Key)0;
// 		
// 		cpk.hasEvent = false;
// 	//	cpk.type = "";
// 		cpk.len = sizeof(cpk);
// 		s_NetworkManager::getInstance().df_send(static_cast<commandPakcetKey *>(&cpk), cpk.len);
// 	}
}
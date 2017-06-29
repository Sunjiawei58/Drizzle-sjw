#pragma once
#ifndef _S_INPUT_MANAGER
#define _S_INPUT_MANAGER
#include "s_Manager.h"
#include <SFML\Graphics.hpp>

namespace df
{
	class s_InputManager : public s_Manager
	{
	private:
		s_InputManager();
		s_InputManager(s_InputManager const&);
		void operator = (s_InputManager const&);
		sf::RenderWindow *p_window;   //why don't have?
	public:
		static s_InputManager &getInstance();

		int startUp();

		void shutDown();

		void getInput();

	
		
	};
}

#endif

#include "GameManager2.h"
#include "LogManager2.h"
#include "s_WorldManager.h"
#include "s_GraphicsManager.h"
#include "s_inputManager.h"
#include "s_NetworkManager.h"
#include "Clock.h"
//#include <Windows.h>
#include <mmsystem.h>
#include "Ship.h"
namespace df{

	
	GameManager2::GameManager2()
	{
		score = 0;
		game_over = false;
		frame_time = 0;
		step_count = 0;
		
	}


	GameManager2& GameManager2::getInstance()
	{
		static GameManager2 *game_manager = NULL;
		if (!game_manager)
		{
			game_manager = new GameManager2;
		}
		return *game_manager;                         // return value should be &game_manager?
	}
	int GameManager2::startUp()
	{
		
		LogManager2 &log_manager = LogManager2::getInstance();
		s_GraphicsManager &graphic_manager = s_GraphicsManager::getInstance();
		s_WorldManager &world_manager = s_WorldManager::getInstance();
		//if (log_manager.startUp(0))
		//{
			
			timeBeginPeriod(1);
			setGameOver(false);
			log_manager.writeLog("Game manager startup\n");

			if (world_manager.isStarted())
			{
				log_manager.writeLog("world manager started up");
				if (graphic_manager.isStarted())
				{
					log_manager.writeLog("graphic manager started up");
					world_manager.setBoundary(s_Box(Position(0,0),graphic_manager.getHorizontal(), graphic_manager.getVertical()));
					s_Manager::startUp();
					
				}
			}

			return 1;
		//}
		
		//else return 0;
	}
	void GameManager2::shutDown()
	{
		LogManager2 &log_manager = LogManager2::getInstance();
		log_manager.writeLog("Game manager close down...\n");
		log_manager.shutDown();
		setGameOver(true);
		timeEndPeriod(1);
	}

	bool GameManager2::isValid(std::string event_name) const
	{
		// if the event is step events
		return 1;
	}
	void GameManager2::run()
	{
		
		Clock *clock = new Clock();
		//long int before_tm;   // changed long to double
		long int loop_time;
		int i = 0;
		while (i<1000 && game_over == false)
		{
			std::string score_content = "Score is ";
			score_content.append(std::to_string(score));
			df::s_GraphicsManager::getInstance().drawString(df::Position(0, 0), score_content, df::RIGHT_JUSTIFIED, df::WHITE);
			// set the previous time (already done)
			s_NetworkManager::getInstance().checkCommPack();
			loop_time = clock->split();
			LogManager2::getInstance().writeLog("the total tw takes %8d\n", loop_time);
			s_WorldManager::getInstance().draw();
			loop_time = clock->split();
			LogManager2::getInstance().writeLog("the draw(send) takes %8d\n", loop_time);
			s_GraphicsManager::getInstance().swapBuffers();   // for the display
			
		
			s_WorldManager::getInstance().update();

			// sending the graphic command
			

			// should check whether network has command package.
			
			
			//s_InputManager::getInstance().getInput();
			// do step event 
				
				loop_time = clock->split();// set the after time.
				LogManager2::getInstance().writeLog("%8d\n",loop_time );
				if (loop_time <= 33)
				{
					Sleep(33 - loop_time);
				}
				LogManager2::getInstance().writeLog("%8d\n", clock->delta());
				//Sleep(FRAME_TIME_DEFAULT - loop_time);
			
			//this->setGameOver(true);
			//sleep for the rest of time.
				i++;
		}
	}
	void GameManager2::setGameOver(bool game_over)
	{
		this->game_over = game_over;
	}
	bool GameManager2::getGameOver() const
	{
		return this->game_over;
	}
	int GameManager2::getFrameTime() const
	{
		return this->frame_time;
	}
	int GameManager2::getStepCount() const
	{
		return this->step_count;
	}

}


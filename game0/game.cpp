//
// game.cpp
// 

// Engine includes.
//#include "ResourceManager.h"  //to load the sprite
//#include "GameManager.h"
#include "vs-2013\Logmanager2.h"
#include "vs-2013\GameManager2.h"
#include "vs-2013\s_GraphicsManager.h"
#include "vs-2013\s_ResourceManager.h"
#include "vs-2013\s_NetworkManager.h"
#include "vs-2013\s_WorldManager.h"
#include "vs-2013\s_InputManager.h"
#include <windows.h>

#include "vs-2013\Saucer.h"
#include "vs-2013\Ship.h"
#include "vs-2013\s_Object.h"
#include "vs-2013\s_timeWarp.h"
#include "vs-2013\SaucerTest.h"
//#include "Position.h"
#include "vs-2013\bullet.h"
#include "vs-2013\Score.h"
void loadResource(void)
{
	df::s_ResourceManager &resource_manager = df::s_ResourceManager::getInstance();

	resource_manager.loadSprite("sprites/saucer-spr.txt", "saucer");
	resource_manager.loadSprite("sprites/ship-spr.txt", "ship");
	resource_manager.loadSprite("sprites/bullet-spr.txt", "bullet");
	resource_manager.loadSprite("sprites/gameover-spr.txt", "GameOver");
}
void populateWorld(void)
{
 
	//new Ship;
	//new bullet;
	//new Saucer;
	//Score *sc = new Score();
	
	Saucer *saucer2 = new Saucer();
	saucer2->setPosition(df::Position(50,10));
	saucer2->setXVelocity(-0.4f);
	saucer2->setYVelocity(0);

	Saucer *saucer3 = new Saucer();
	saucer3->setPosition(df::Position(50,14));
	saucer3->setXVelocity(-0.4f);
	saucer3->setYVelocity(0);
}

int main(int argc, char *argv[]) {   //main ->test
	

	std::cout << "Welcome to Drizzle" << std::endl;
	std::cout << "Please input the test ID" << std::endl;
	
	int id = 0;
	std::cin >> id;
	std::cout << "please input the session ID (from 0 to 9)" << std::endl;
	int session = 0;
	std::cin >> session;

	//Score *sc = new Score();
	df::LogManager2 &log_manager = df::LogManager2::getInstance();
	// Start up game manager.
	df::GameManager2 &game_manager = df::GameManager2::getInstance();
	df::s_ResourceManager &resource_manager = df::s_ResourceManager::getInstance();
	df::s_NetworkManager &network_manager = df::s_NetworkManager::getInstance();
	df::s_WorldManager &world_manager = df::s_WorldManager::getInstance();
	df::s_GraphicsManager &graphics_manager = df::s_GraphicsManager::getInstance();
	df::s_InputManager &input_manager = df::s_InputManager::getInstance();
	df::s_timeWarp &time_warp = df::s_timeWarp::getInstance();

	
	/*if (!game_manager.startUp())  {


		game_manager.shutDown();
		log_manager.writeLog("111\n");
		return 0;
	}*/
	//resource_manager.startUp();
	//loadResource();
	//resource_manager.shutDown();
	
	/* log_manager.startUp();

	 int count =log_manager.writeLog("this is for test for writingLog\n");
	 log_manager.writeLog("%s:the return value is %d\n",log_manager.getTimeString(),count);
	 log_manager.setLogLevel(3);
	 count = log_manager.getLogLevel();

	 log_manager.writeLog(4, "this is for testing the log_level %d \n",count);
	 log_manager.shutDown();*/   //test log_manager


	// Set flush of logfile during development (when done, make false).
	// log_manager.setFlush(true);



	///test game_manager



	// Show splash screen.

	//df::splash();

	 
	 // populateWorld();
	world_manager.startUp();
	
	log_manager.startUp(id*10 + session);
	loadResource();
	graphics_manager.startUp();

	network_manager.startUp();
	network_manager.df_accept();
	
	Saucer * s = new Saucer();
	//s->generateSaucerTestCPU();
	s->generateSaucerForImg();
	//populateWorld();
	Ship *player = new Ship();
//	SaucerTest *n_obj1 = new SaucerTest();
// 	SaucerTest *n_obj2 = new SaucerTest();


// 	n_obj1->setID(1);
// 	n_obj1->hp = 10;
// 	n_obj2->setID(2);
// 	n_obj2->hp = 20;
/*	loadResource();
	populateWorld();   // new a saucer
	graphics_manager.startUp();
	input_manager.startUp();
	graphics_manager.drawCh(df::Position(10, 5), '*', df::RED);
	graphics_manager.swapBuffers();
	Sleep(1000);
		
	world_manager.draw();
	world_manager.update();  // do the deep copy     game world 0
	Sleep(1000);
	df::ObjectList2 objpre = world_manager.getAllObjects();
	df::ObjectListIterator2 li = df::ObjectListIterator2(&objpre);
	Saucer * saucer1 = dynamic_cast<Saucer*>(li.currentObject());
	
	world_manager.draw();
	world_manager.update();   /// game world 1
	Sleep(100);

	
	world_manager.draw();
	world_manager.update();   // game world 2
	
	Sleep(100);
// 	n_obj1->hp = 40;
										//doing the time warp test below//
	unsigned int current_time = df::s_timeWarp::getInstance().current_time_counter - 1;
	df::WorldFrameByTimeCounter *world_frame = df::s_timeWarp::getInstance().getWorldFrameByTimeCounter(current_time -2);
	df::ObjectList2 objCurrent = world_frame->getObjectList();
	df::ObjectListIterator2 li2 = df::ObjectListIterator2(&objCurrent);

	Saucer * obj0 = dynamic_cast<Saucer*>(li2.currentObject());
	obj0->setPosition(df::Position(obj0->getPosition().getX(), obj0->getPosition().getY() + 5));  // apply changes
	df::s_timeWarp::getInstance().reApplyGameWorlds(*world_frame);

	df::ObjectList2 objTest = df::s_WorldManager::getInstance().getAllObjects();
	df::ObjectListIterator2 li3 = df::ObjectListIterator2(&objTest);

	Saucer *obj1 = dynamic_cast<Saucer*>(li3.currentObject());
	df::LogManager2::getInstance().writeLog("the x position is %d ", obj1->getPosition().getX());
	df::LogManager2::getInstance().writeLog("the y position is %d ", obj1->getPosition().getY());  // latest version
	world_manager.draw();
	Sleep(100);
	
	*/
	//log_manager.writeLog("the previous hp is %d",res);
	//retreat the previous one.   // google regression test.  // virtual pointer?  -->next step

	//-----------------test graphics---------------------------//
	
/*	df::s_GraphicsManager &graphics_manager = df::s_GraphicsManager::getInstance();
	
	graphics_manager.startUp();
	graphics_manager.drawCh(df::Position(10, 5), '*', df::WHITE);

	graphics_manager.drawCh(df::Position(5, 5), '*', df::RED);

	graphics_manager.drawCh(df::Position(2, 8), '*', df::WHITE);

	graphics_manager.drawCh(df::Position(10, 2), '*', df::WHITE);

	graphics_manager.drawCh(df::Position(4, 20), '*', df::WHITE);
	graphics_manager.drawString(df::Position(20, 20), "Hello game Miss me?",df::CENTER_JUSTIFIED, df::WHITE);
	graphics_manager.swapBuffers();


	Sleep(2000);
	graphics_manager.shutDown();
	
	*/

	//game_manager.run();

	


	///   for network manager test  / /////
	if ((session == 0) || (session == 1) || (session == 4) || (session == 5) || (session == 8))
	{
		df::s_timeWarp::getInstance().timeWarpOn = false;
	}

	else df::s_timeWarp::getInstance().timeWarpOn = true;
	game_manager.run();
	df::LogManager2::getInstance().writeLog("the final score is %d",df::GameManager2::getInstance().score);



	
	return 1;

	



}
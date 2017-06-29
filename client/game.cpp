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
#include <windows.h>

#include "vs-2013\Saucer.h"

void loadResource(void)
{
	df::s_ResourceManager &resource_manager = df::s_ResourceManager::getInstance();

	resource_manager.loadSprite("sprites/saucer-spr.txt", "saucer");
}
void populateWorld(void)
{
	new Saucer;
}
int main(int argc, char *argv[]) { 
	


	
	//main ->test
	df::LogManager2 &log_manager = df::LogManager2::getInstance();

	// Start up game manager.
	df::GameManager2 &game_manager = df::GameManager2::getInstance();
	
	
	if (!game_manager.startUp())  {


		game_manager.shutDown();
		log_manager.writeLog("111\n");
		return 0;
	}



	// Show splash screen.

	//df::splash();

	//  loadResource();
	//  populateWorld();
	df::s_ResourceManager &resource_manager = df::s_ResourceManager::getInstance();

	 
	//-------------------test graphic manager over---------------/
	resource_manager.startUp();
	 
	 

	df::s_NetworkManager &network_manager = df::s_NetworkManager::getInstance();
	df::s_GraphicsManager &graphics_manager = df::s_GraphicsManager::getInstance();
	df::s_InputManager &input_manager = df::s_InputManager::getInstance();
	graphics_manager.startUp();
	network_manager.startUp();
	network_manager.df_connect("127.0.0.1", DRAGONFLY_PORT);
	input_manager.startUp();

	game_manager.run();
	//test network manager_client //
/*	network_manager.startUp();
	network_manager.df_connect("127.0.0.1",DRAGONFLY_PORT);
	std::string command;
	df::graphicsPacketCh g_packet;
	void * g = static_cast<df::graphicsPacketCh *>(&g_packet);
	while (1)
	{
	network_manager.df_receive(g,0,false);
	log_manager.writeLog("command is %c", g_packet.content);
	log_manager.writeLog("command is %d", g_packet.color);
	graphics_manager.drawCh(df::Position(g_packet.x, g_packet.y), g_packet.content, g_packet.color);	
	graphics_manager.swapBuffers();
	}
	graphics_manager.shutDown();

	//system("pause");
	network_manager.close();

	//log_manager.writeLog(MOTD.c_str());

	log_manager.setFlush();
	//  game_manager.run();
	 
	// Shut everything down.
	// game_manager.shutDown();



	*/

	return 1;



}
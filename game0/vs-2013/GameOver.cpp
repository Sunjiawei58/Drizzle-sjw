#include "GameOver.h"
#include "Logmanager2.h"
#include "s_ResourceManager.h"
#include "s_WorldManager.h"


GameOver::GameOver()
{

	
	df::LogManager2 &log_manager = df::LogManager2::getInstance();
	df::s_ResourceManager &resource_manager = df::s_ResourceManager::getInstance();
	df::s_WorldManager & world_manager = df::s_WorldManager::getInstance();

	df::s_Sprite *p_temp_sprite = resource_manager.getSprite("GameOver");

	if (!p_temp_sprite)
	{
		log_manager.writeLog("gameover::gameover(): Warning ! Sprite '%s' not found", "GameOver");
	}
	else
	{
		setSprite(p_temp_sprite);
		setType("GameOver");
		setXVelocity(0);
		setSpriteSlowdown(5);
		setBox(df::s_Box(df::Position(0, 0), p_temp_sprite->getHeight(), p_temp_sprite->getWidth()));
		int vert = world_manager.getBoundary().getVertical();
		df::Position pos(40, 10);
		setPosition(pos);
	}
}


GameOver::~GameOver()
{
}

int GameOver::eventHandler(const df::s_Event * p)
{
	return 0;
}

GameOver * GameOver::clone() const
{
	return new GameOver(*this);
}

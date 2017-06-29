#include "Saucer.h"

#include "LogManager2.h"
#include "s_WorldManager.h"
#include "s_ResourceManager.h"
#include "s_EventOut.h"
#include <stdlib.h>;
Saucer::Saucer()
{
	df::LogManager2 &log_manager = df::LogManager2::getInstance();
	df::s_ResourceManager &resource_manager = df::s_ResourceManager::getInstance();
	df::s_WorldManager & world_manager = df::s_WorldManager::getInstance();

	//set up the "saucer" sprite

	df::s_Sprite *p_temp_sprite = resource_manager.getSprite("saucer");
	if (!p_temp_sprite)
	{
		log_manager.writeLog("Saucer::Saucer(): Warning ! Sprite '%s' not found", "saucer");
	}
	else
	{

		setSprite(p_temp_sprite);
		setSpriteSlowdown(4);

		setType("Saucer");

		setXVelocity(5);

		int world_horiz = world_manager.getBoundary().getHorizontal();
		int world_vert = world_manager.getBoundary().getVertical();
		df::Position pos(world_horiz / 2, world_vert / 2);
		setPosition(pos);
		moveToStart();
	}
}

int Saucer::eventHander(const df::s_Event *p)
{

	if (p->getType() == df::OUT_EVENT)
	{
		out();
		return 1;
	}
	else return 0;
}
void Saucer::out()
{
	if (getPosition().getX() >= 0)
	{
		return;
	}
	moveToStart();
}
void Saucer::moveToStart()
{
	df::s_WorldManager &world_manager = df::s_WorldManager::getInstance();
	df::Position temp_pos;

	int world_horiz = world_manager.getBoundary().getHorizontal();
	int world_vert = world_manager.getBoundary().getVertical();

	temp_pos.setX(10);
	temp_pos.setY(10);
	//temp_pos.setX(world_horiz + rand() % world_horiz + 3);
	//temp_pos.setY(rand() % (world_vert - 1) + 1);

	world_manager.moveObject(this, temp_pos);
}
Saucer* Saucer::clone() const
{
	return new Saucer(*this);
}
Saucer::~Saucer()
{
}
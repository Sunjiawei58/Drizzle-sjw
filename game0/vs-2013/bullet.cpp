#include "bullet.h"
#include "Logmanager2.h"
#include "s_ResourceManager.h"
#include "s_WorldManager.h"
#include "s_EventCollision.h"
#include "s_EventOut.h"

#include "Ship.h"
#include "GameManager2.h"
#include "ObjectList2.h"
bullet::bullet()
{
	df::LogManager2 &log_manager = df::LogManager2::getInstance();
	df::s_ResourceManager &resource_manager = df::s_ResourceManager::getInstance();
	df::s_WorldManager & world_manager = df::s_WorldManager::getInstance();

	df::s_Sprite *p_temp_sprite = resource_manager.getSprite("bullet");

	if (!p_temp_sprite)
	{
		log_manager.writeLog("Bullet::Bullet(): Warning ! Sprite '%s' not found", "bullet");
	}
	else
	{
		setSprite(p_temp_sprite);
		setType("bullet");
		setXVelocity(0.8f);
		setBox(df::s_Box(df::Position(0, 0), p_temp_sprite->getHeight(), p_temp_sprite->getWidth()));
		int vert = world_manager.getBoundary().getVertical();
		df::Position pos(15, 10);
		setPosition(pos);
	}
}
bullet::bullet(df::Position pos)
{
	df::LogManager2 &log_manager = df::LogManager2::getInstance();
	df::s_ResourceManager &resource_manager = df::s_ResourceManager::getInstance();
	df::s_WorldManager & world_manager = df::s_WorldManager::getInstance();

	df::s_Sprite *p_temp_sprite = resource_manager.getSprite("bullet");

	if (!p_temp_sprite)
	{
		log_manager.writeLog("Bullet::Bullet(): Warning ! Sprite '%s' not found", "bullet");
	}
	else
	{
		setSprite(p_temp_sprite);
		setType("bullet");
		setXVelocity(0.5f);
		setCentered(true);
		setBox(df::s_Box(df::Position(0, 0), p_temp_sprite->getHeight(), p_temp_sprite->getWidth()));
		log_manager.writeLog("the bullet pos is %d,%d", pos.getX(), pos.getY());
		setPosition(pos);
	}
}



bullet::~bullet()
{
}

int bullet::eventHandler(const df::s_Event * p)
{
	if (p->getType() == df::S_COLLISION_EVENT)
	{
		const df::s_EventCollision *eventCollision = static_cast<const df::s_EventCollision*>(p);

 		if ((eventCollision->getObject2()->getType() == "Saucer" && eventCollision->getObject1()->getType() == "bullet") || (eventCollision->getObject1()->getType() == "Saucer" && eventCollision->getObject2()->getType() == "bullet"))
		{
			df::ObjectList2 obj = df::s_WorldManager::getInstance().getAllObjects();
			df::ObjectListIterator2 li = df::ObjectListIterator2(&obj);
			Ship *s = NULL;
			while (!li.isDone())
			{
				if (strcmp(li.currentObject()->getType().c_str(),"Ship") == 0)
				{
					s = static_cast<Ship*>(li.currentObject());
					break;  // only one ship
				}
				li.next();
			}
			if (s!=NULL)
			{
				s->addScore();
			}
			//df::GameManager2::getInstance().score++;
			df::LogManager2::getInstance().writeLog("there is a collision!...");
			df::LogManager2::getInstance().writeLog("the score is %d", s->getScore());
			df::GameManager2::getInstance().score = s->getScore();
		}

		
		df::s_WorldManager::getInstance().markForDeletion(this);
		return 1;
	}
	else if (p->getType() == df::OUT_EVENT)
	{
		out();
		return 1;
	}
	return 0;
}

bullet * bullet::clone() const
{
	return new bullet(*this);
}
int bullet::out()
{
	if (this->getPosition().getX()< 0 || this->getPosition().getX()>df::s_WorldManager::getInstance().getBoundary().getHorizontal())
	{
		df::LogManager2::getInstance().writeLog("the horizontal is %d,out of the bound..", df::s_WorldManager::getInstance().getBoundary().getHorizontal());
		df::s_WorldManager::getInstance().markForDeletion(this);
		return 1;
	}
	else return 0;
}
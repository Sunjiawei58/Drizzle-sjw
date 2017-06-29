


#include "Saucer.h"

#include "LogManager2.h"
#include "s_WorldManager.h"
#include "s_ResourceManager.h"
#include "s_EventOut.h"
#include "s_EventKeyBoard.h"
#include "s_EventCollision.h"
#include "Ship.h"
#include "GameOver.h"
#include <stdlib.h>;

int Saucer::totalNum = 0;
int NumOfSaucer()
{
	df::ObjectList2 li = df::s_WorldManager::getInstance().getAllObjects();
	df::ObjectListIterator2 it = df::ObjectListIterator2(&li);
	int total = 0;
	while (!it.isDone())
	{
		if (it.currentObject()->getType() == "Saucer")
		{
			total++;
		}
		it.next();
	}
	return total;
}
Saucer::Saucer()
{
	totalNum++;
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
		setXVelocity(-0.4f);
		setBox(df::s_Box(df::Position(0,1),p_temp_sprite->getWidth(),p_temp_sprite->getHeight()-1));
		int world_horiz = world_manager.getBoundary().getHorizontal();
		int world_vert = world_manager.getBoundary().getVertical();
		df::Position pos(world_horiz / 2, world_vert / 2);
		//setPosition(pos);
		setPosition(df::Position(10, 10));
		
		//moveToStart();
	}
}

int Saucer::eventHandler(const df::s_Event *p)
{
	
	/*if (p->getType() == df::S_KEYBOARD_EVENT)
	{
		const df::s_EventKeyBoard *eventKey = static_cast<const df::s_EventKeyBoard *>(p);

		if (eventKey->getKey() == df::Input::DownArrow && eventKey->getKeyboardAction() != df::UNDEFINED_KEYBOARD_ACTION)
		{
			this->setPosition(df::Position(this->getPosition().getX(), this->getPosition().getY() + 1));
			return 1;
		}
		else if (eventKey->getKey() == df::Input::UpArrow && eventKey->getKeyboardAction() == df::KEY_PRESSED)
		{
			this->setPosition(df::Position(this->getPosition().getX(), this->getPosition().getY() - 1));
			return 1;
		}
		else if (eventKey->getKey() == df::Input::LeftArrow && eventKey->getKeyboardAction() == df::KEY_PRESSED)
		{
			this->setPosition(df::Position(this->getPosition().getX() - 1, this->getPosition().getY()));
			return 1;
		}
		else if (eventKey->getKey() == df::Input::RightArrow && eventKey->getKeyboardAction() == df::KEY_PRESSED)
		{
			this->setPosition(df::Position(this->getPosition().getX() + 1, this->getPosition().getY()));
			return 1;
		}
	}*/
	if (p->getType() == df::S_COLLISION_EVENT)
	{
		const df::s_EventCollision *eventCollision = static_cast<const df::s_EventCollision*>(p);
		//df::LogManager2::getInstance().writeLog("there is a collision!...");
		df::s_WorldManager::getInstance().markForDeletion(this);
		totalNum--;
	//	generateSaucer();
		return 1;

	}
	if (p->getType() == df::OUT_EVENT)
	{
		out();
		return 1;
	}
	else return 0;
}
void Saucer::out()
{
	if (getPosition().getX() < 0)
	{
		df::s_WorldManager::getInstance().markForDeletion(this);
		totalNum--;
		int random = rand()%2+1;   // from 1 to 2;


		df::ObjectList2 obj = df::s_WorldManager::getInstance().getAllObjects();
		df::ObjectListIterator2 li = df::ObjectListIterator2(&obj);
		Ship *s = NULL;
		int miss = 0;
		while (!li.isDone())
		{
			if (strcmp(li.currentObject()->getType().c_str(), "Ship") == 0)
			{
				s = static_cast<Ship*>(li.currentObject());
				break;  // only one ship
			}
			li.next();
		}
		if (s != NULL)
		{
			s->missSaucer();
			miss = s->getMiss();


			if (miss >= 0 && NumOfSaucer()<=maxEnemy)
			{
				for (int i = 0; i < random; ++i)
				{

					Saucer *new_saucer = new Saucer();
					int ran_posX = df::s_WorldManager::getInstance().getBoundary().getHorizontal() - 5 + rand() % 4;
					int ran_posY = df::s_WorldManager::getInstance().getBoundary().getVertical() / 4 * (i + 1) + (rand() % 7 - 3);
					df::Position ran_pos(ran_posX, ran_posY);

					df::ObjectList2 collision_list = df::s_WorldManager::getInstance().isCollision(new_saucer, ran_pos);
					while (!collision_list.isEmpty())
					{
						ran_pos.setX(ran_pos.getX() - 2);
						ran_pos.setY(ran_pos.getY() + 2);
						collision_list = df::s_WorldManager::getInstance().isCollision(new_saucer, ran_pos);
					}
					new_saucer->setPosition(ran_pos);
					new_saucer->setXVelocity(-0.4f);
					new_saucer->setYVelocity(0);
				}
				return;
			}
			else
			{
				df::ObjectList2 obj = df::s_WorldManager::getInstance().getAllObjects();
				df::ObjectListIterator2 li = df::ObjectListIterator2(&obj);
				while (!li.isDone())
				{
					df::s_Object *temObj = li.currentObject();
					df::s_WorldManager::getInstance().markForDeletion(temObj);
					li.next();
				}
				new GameOver;
				return;
			}
		}
	}
	else return;
	//moveToStart();
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

void Saucer::generateSaucer()
{
	if (NumOfSaucer()<= maxEnemy)
	{
		int random = rand() % 3 + 1;   // from 1 to 2;
		for (int i = 0; i < random; i++)
		{
			Saucer *new_saucer = new Saucer;
			int ran_posX = df::s_WorldManager::getInstance().getBoundary().getHorizontal() - 5 + rand() % 4;
			int ran_posY = df::s_WorldManager::getInstance().getBoundary().getVertical() / 4 * (i + 1) + (rand() % 7 - 3);
			df::Position ran_pos(ran_posX, ran_posY);

			df::ObjectList2 collision_list = df::s_WorldManager::getInstance().isCollision(new_saucer, ran_pos);
			while (!collision_list.isEmpty())
			{
				ran_pos.setX(ran_pos.getX() - 2);
				ran_pos.setY(ran_pos.getY() + 1);
				collision_list = df::s_WorldManager::getInstance().isCollision(new_saucer, ran_pos);
			}
			new_saucer->setPosition(ran_pos);

		}
	}
	
}
void Saucer::generateSaucerTestCPU()
{
	if (NumOfSaucer() <= maxEnemy)
	{
		for (int i = NumOfSaucer(); i < maxEnemy; i++)
		{
			Saucer *new_saucer = new Saucer;
			int ran_posX = df::s_WorldManager::getInstance().getBoundary().getHorizontal() - 5 + rand() % 4;
			int ran_posY = df::s_WorldManager::getInstance().getBoundary().getVertical() / 4 * (i + 1) + (rand() % 7 - 3);
			df::Position ran_pos(ran_posX, ran_posY);

			df::ObjectList2 collision_list = df::s_WorldManager::getInstance().isCollision(new_saucer, ran_pos);
			while (!collision_list.isEmpty())
			{
				ran_pos.setX(ran_pos.getX() - 2);
				ran_pos.setY(ran_pos.getY() + 1);
				collision_list = df::s_WorldManager::getInstance().isCollision(new_saucer, ran_pos);
			}
			new_saucer->setPosition(ran_pos);

		}
	}

}
void Saucer::generateSaucerForImg()
{
	if (NumOfSaucer() <= maxEnemy)
	{
		for (int i = NumOfSaucer(); i < maxEnemy; i++)
		{
			Saucer *new_saucer = new Saucer;
			int numVertcal = df::s_WorldManager::getInstance().getBoundary().getVertical() / 4;
			int numHori = df::s_WorldManager::getInstance().getBoundary().getHorizontal() / 6;
			int pos_y = (i / numHori) * 4;
			int pos_x = (i % numHori) * 6;
// 			int ran_posX = df::s_WorldManager::getInstance().getBoundary().getHorizontal() - 5 + rand() % 4;
// 			int ran_posY = df::s_WorldManager::getInstance().getBoundary().getVertical() / 4 * (i + 1) + (rand() % 7 - 3);
			df::Position ran_pos(pos_x, pos_y);

// 			df::ObjectList2 collision_list = df::s_WorldManager::getInstance().isCollision(new_saucer, ran_pos);
// 			while (!collision_list.isEmpty())
// 			{
// 				ran_pos.setX(ran_pos.getX() - 2);
// 				ran_pos.setY(ran_pos.getY() + 1);
// 				collision_list = df::s_WorldManager::getInstance().isCollision(new_saucer, ran_pos);
// 			}
			new_saucer->setPosition(ran_pos);
			new_saucer->setXVelocity(0);
			new_saucer->setYVelocity(0);
		}
	}
}
Saucer* Saucer::clone() const
{
	return new Saucer(*this);
}
Saucer::~Saucer()
{
}

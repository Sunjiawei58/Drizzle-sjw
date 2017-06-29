#include "Ship.h"
#include "Logmanager2.h"
#include "s_WorldManager.h"
#include "s_ResourceManager.h"
#include "s_EventKeyBoard.h"
#include "s_EventCollision.h"
#include "GameManager2.h"
#include "GameOver.h"
#include "bullet.h"
Ship::Ship()
{
	hp = 2;  // default
	score = 0;
	missMax = 5;
	df::LogManager2 &log_manager = df::LogManager2::getInstance();
	df::s_ResourceManager &resource_manager = df::s_ResourceManager::getInstance();
	df::s_WorldManager & world_manager = df::s_WorldManager::getInstance();

	df::s_Sprite *p_temp_sprite = resource_manager.getSprite("ship");

	if (!p_temp_sprite)
	{
		log_manager.writeLog("Ship::Ship(): Warning ! Sprite '%s' not found", "ship");
	}
	else
	{
		setSprite(p_temp_sprite);
		setType("Ship");
		setXVelocity(0);
		setCentered(true);
		setBox(df::s_Box(df::Position(0,0),p_temp_sprite->getHeight(),p_temp_sprite->getWidth()));
		int vert = world_manager.getBoundary().getVertical();
		df::Position pos(5, 10);
		setPosition(pos);
		
	}
}


// Ship & Ship::getInstance()
// {
// 	static Ship *ship = NULL;
// 	if (!ship)
// 	{
// 		ship = new Ship;
// 	}
// 	else return *ship;
// 	// TODO: insert return statement here
// }

Ship::~Ship()
{
}

int Ship::eventHandler(const df::s_Event * p)
{
	if (p->getType() == df::S_KEYBOARD_EVENT)
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
		else if (eventKey->getKey() == df::Input::Space && eventKey->getKeyboardAction() == df::KEY_PRESSED)
		{
			df::LogManager2::getInstance().writeLog("there should be a bullet...");
			//new bullet;
			new bullet(df::Position(this->getPosition().getX()+this->getSprite()->getWidth()/2 + 1,this->getPosition().getY()));
		}
	}
	else if (p->getType()== df::S_COLLISION_EVENT)
	{
		const df::s_EventCollision *collision = static_cast<const df::s_EventCollision*>(p);
		if ((collision->getObject2()->getType() == "Saucer" && collision->getObject1()->getType() == "Ship") || (collision->getObject2()->getType() == "Ship" && collision->getObject1()->getType() == "Saucer"))
		{
			--hp;
			df::LogManager2::getInstance().writeLog("you are being attacked...");
			if (hp<=0)
			{
				df::ObjectListIterator2 li = df::ObjectListIterator2(&df::s_WorldManager::getInstance().getAllObjects());
				while (!li.isDone())
				{
					df::s_WorldManager::getInstance().markForDeletion(li.currentObject());
					li.next();
				}  // delete all stuff and then generate game over animation.
				new GameOver;
				//df::GameManager2::getInstance().setGameOver(true);

			}
		}
	}
	return 0;
}

Ship * Ship::clone() const
{
	return new Ship(*this);
}

int Ship::getScore()
{
	return score;
}

void Ship::addScore()
{
	score++;
}

void Ship::missSaucer()
{
	missMax--;
}

int Ship::getMiss()
{
	return missMax;
}

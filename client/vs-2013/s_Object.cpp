#include "s_Object.h"
#include "s_WorldManager.h"
#include "s_GraphicsManager.h"
#include "math.h"
using namespace df;

s_Object::s_Object()
{
	sprite_center = true;
	sprite_index = 0;
	sprite_slowdown = 1;   //slowdown rate(1->no slowdown 0->stop)
	sprite_slowdown_count = 0;   //slowdown counter
	id = 0;				//unique Object ID
	type = ""; // user-defined type
			   //Position in the game world
	solid = collision::HARD;
	altitude = 0;
	x_velocity = 0;//extended to support the collision
	x_velocity_countdown = 0;
	y_velocity = 0;
	y_velocity_countdown = 0;
	s_WorldManager::getInstance().insertObject(this);
}


s_Object::~s_Object()
{
}
void s_Object::setID(int id)
{
	this->id = id;
}
int s_Object::getID() const
{
	return this->id;
}
void s_Object::setType(std::string new_type)
{
	type = new_type;
}  
std::string s_Object::getType() const
{
	return this->type;
}
void s_Object::setPosition(Position pos)
{
	this->pos = pos; 
}
Position s_Object::getPosition() const
{
	return this->pos;
}
int s_Object::eventHandler(const s_Event *p_e)
{
	return 0;                  // simply do nothing.
}
void s_Object::draw()
{

	if (p_sprite == NULL)
	{
		return;   // empty
	}

	int index = getSpriteIndex();

	s_GraphicsManager::getInstance().drawFrame(pos, p_sprite->getFrame(index), sprite_center, p_sprite->getColor());
	

	if (getSpriteSlowdown() == 0)
	{
		return;    // frozen animation
	}

	int count = getSpriteSlowdownCount();
	count++;

	if (count >= getSpriteSlowdown())
	{
		count = 0;

		index++;
		if (index >= p_sprite->getFrameCount())
		{
			index = 0;
		}
	}

	setSpriteSlowdownCount(count);
	setSpriteIndex(index);


	// to be done in the inherity class.
}
int s_Object::setAltitude(int new_altitude)
{
	if (altitude = new_altitude)
	{
		return 1;
	}
	else return 0;
}
int s_Object::getAltitude() const
{
	return	altitude;
}

void s_Object::setXVelocity(float new_x_velocity)
{
	x_velocity = new_x_velocity;
}
float s_Object::getXVelocity() const
{
	return x_velocity;
}

void s_Object::setYVelocity(float new_y_velocity)
{
	y_velocity = new_y_velocity;
}
float s_Object::getYVelocity() const
{
	return y_velocity;
}

int s_Object::getXVelocityStep()
{
	if (x_velocity == 0)
	{
		return 0;
	}

	x_velocity_countdown -= fabs(x_velocity);
	if (x_velocity_countdown > 0)
	{
		return 0;
	}

	int spaces = (int)floor(1 - x_velocity_countdown);
	x_velocity_countdown = (float)(1 + fmod(x_velocity_countdown, 1));

	if (x_velocity > 0)
	{
		return spaces;
	}
	else return(-1 * spaces);
}

int s_Object::getYVelocityStep()
{
	if (y_velocity == 0)
	{
		return 0;
	}

	y_velocity_countdown -= fabs(y_velocity);
	if (y_velocity_countdown > 0)
	{
		return 0;
	}

	int spaces =(int) floor(1 - y_velocity_countdown);
	y_velocity_countdown =(float)( 1 + fmod(y_velocity_countdown, 1));

	if (y_velocity > 0)
	{
		return spaces;
	}
	else return(-1 * spaces);
}
bool s_Object::isSolid() const
{
	return solid == df::collision::HARD ? true : false;
}

void s_Object::setSprite(s_Sprite *p_new_sprite,bool set_box)
{
	p_sprite = p_new_sprite;
	if (set_box == true)
	{
		box.setHorizontal(p_sprite->getWidth());
		box.setVertical(p_sprite->getHeight());
	}
}

s_Sprite* s_Object::getSprite() const
{
	return p_sprite;
}

void s_Object::setCentered(bool centered)
{
	sprite_center = centered;
}

bool s_Object::isCentered() const
{
	if (sprite_center == true)
	{
		return true;
	}
	else return false;
}

void s_Object::setSpriteIndex(int new_sprite_index)
{
	sprite_index = new_sprite_index;
}

int s_Object::getSpriteIndex() const
{
	return sprite_index;
}

void s_Object::setSpriteSlowdown(int new_sprite_slowdown)
{
	sprite_slowdown = new_sprite_slowdown;
}

int s_Object::getSpriteSlowdown() const
{
	return sprite_slowdown;
}

void s_Object::setSpriteSlowdownCount(int new_sprite_slowdown_count)
{
	sprite_slowdown_count = new_sprite_slowdown_count;
}

int s_Object::getSpriteSlowdownCount()const
{
	return sprite_slowdown_count;

}
void s_Object::setBox(s_Box new_box)
{
	box = new_box;
}
s_Box s_Object::getBox() const
{
	return box;
}
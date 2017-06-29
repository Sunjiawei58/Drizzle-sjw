#ifndef _OBJECT_H_
#define _OBJECT_H_
#include <string>
#include "Position.h"
#include "s_Event.h"
#include "s_Sprite.h"
#include "s_Box.h"
namespace df
{
	namespace collision{


		enum Solidness
		{
			HARD,
			SOFT,
			SPECTRAL,
		};
	}
	class s_Object
	{
		
	private:
		s_Sprite *p_sprite;
		bool sprite_center;
		int sprite_index;
		int sprite_slowdown;   //slowdown rate(1->no slowdown 0->stop)
		int sprite_slowdown_count;   //slowdown counter
		int id;				//unique Object ID
		std::string type;  // user-defined type
		Position pos;     //Position in the game world
		collision::Solidness solid;
		int altitude;
		float x_velocity;  //extended to support the collision
		float x_velocity_countdown;
		float y_velocity;
		float y_velocity_countdown;

		s_Box box;
	public:

		//set default values and add objets to game world
		s_Object();  
		virtual ~s_Object();

		void setID(int id);

		int getID() const;

		void setType(std::string type);

		std::string getType() const;

		void setPosition(Position pos);

		Position getPosition() const;

		virtual int eventHandler(const s_Event *p_e);
		virtual void draw();

		int setAltitude(int new_altitude);

		int getAltitude() const;

		void setXVelocity(float new_x_velocity);
		float getXVelocity() const;

		void setYVelocity(float new_y_velocity);
		float getYVelocity() const;

		int getXVelocityStep();

		int getYVelocityStep();

		bool isSolid() const;

		//sprite
		
		void setSprite(s_Sprite *p_new_sprite, bool set_box = true);  // without box

		s_Sprite *getSprite() const;

		void setCentered(bool centered);

		bool isCentered() const;

		void setSpriteIndex(int new_sprite_index);

		int getSpriteIndex() const;

		void setSpriteSlowdown(int new_sprite_slowdown);

		int getSpriteSlowdown() const;

		void setSpriteSlowdownCount(int new_sprite_slowdown_count);

		int getSpriteSlowdownCount()const;

		//box

		void setBox(s_Box new_box);
		s_Box getBox() const;

		virtual s_Object* clone() const = 0;
	};

}
#endif
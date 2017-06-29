#include "s_WorldManager.h"
#include "s_Utility.h"
#include "s_EventCollision.h"
#include "s_EventOut.h"
#include "s_timeWarp.h"
#include "s_GraphicsManager.h"
#include "s_NetworkManager.h"
#include "Logmanager2.h"
#include "Clock.h"
using namespace df;

s_WorldManager::s_WorldManager()
{
	this->setType("WorldManager");   // set the type of manager.
	boundary.setHorizontal(df::WINDOW_HORIZONTAL_CHARS_DEFAULT);
	boundary.setVertical(df::WINDOW_VERTICAL_CHARS_DEFAULT);

	view.setHorizontal(0);
	view.setVertical(0);
}

s_WorldManager& s_WorldManager::getInstance()
{
	static s_WorldManager *world_manager = NULL;
	if (!world_manager)
	{
		world_manager = new s_WorldManager;
	}
	return *world_manager;
}
int s_WorldManager::startUp()
{
	
	updates.clear();
	deletions.clear();      // initiate everything to empty
	s_Manager::startUp();
	return 0;   // return value 0?
}
void s_WorldManager::shutDown()
{
	ObjectList2 ol = updates;
	ObjectListIterator2 li = ObjectListIterator2(&ol);
	for (li.first(); !li.isDone(); li.next())
	{
		updates.remove(li.currentObject());
	} // deletes the updates.

	ol = deletions;
	li = ObjectListIterator2(&ol);
	for (li.first(); !li.isDone(); li.next())
	{
		deletions.remove(li.currentObject());
	}   // deletes the deletions
	// shutdown game world (delete all game world objects) 
}
int s_WorldManager::insertObject(s_Object *p_o)
{
	if (updates.insert(p_o))
	{
		return 1; // 1 for ok.
	}
	else return 0;  // 0 for not ok.
}
int s_WorldManager::removeObject(s_Object *p_o)     //remove the objects from updates.
{
	if (updates.remove(p_o))
	{
		return 1;  // 1 for ok. 0  for not ok.
	}
	else return 0;
}
void s_WorldManager::update()    //delete objects marked for deletions.
{
	Clock *clock = new Clock();
	//long int before_tm;   // changed long to double
	long int loop_time;
	ObjectList2 ol = deletions;
	ObjectListIterator2	li = ObjectListIterator2(&ol);

	for (li.first(); !li.isDone(); li.next())
	{
		removeObject(li.currentObject());
	}            /// the only thing to do now is to delete the deletions objects from the updates.



	ol = updates;
	li = ObjectListIterator2(&ol);
	int i = 0;
	for (li.first(); !li.isDone(); li.next())
	{
		i++;
		int x = li.currentObject()->getXVelocityStep();
		int y = li.currentObject()->getYVelocityStep();

		if (x != 0 || y != 0)   //? how to make sure did move? 
		{
			Position old_pos = li.currentObject()->getPosition();
			Position new_pos (old_pos.getX() + x, old_pos.getY() + y);

			if (moveObject(li.currentObject(), new_pos))
			{
				li.currentObject()->setPosition(new_pos);
			}
			
			//move Object to new pos;

		}
		
	}
	loop_time = clock->split();
	LogManager2::getInstance().writeLog("the size of update list is%d", i);
	LogManager2::getInstance().writeLog("update takes %8d", loop_time);
	/*to do the deep copy while in the update*/
	unsigned int time_counter = s_timeWarp::getInstance().current_time_counter;
	WorldFrameByTimeCounter world_frame = s_timeWarp::getInstance().deepCopy(time_counter);
	s_timeWarp::getInstance().saveWorldFrame(world_frame);
	s_timeWarp::getInstance().current_time_counter++;
	loop_time = clock->split();
	LogManager2::getInstance().writeLog("deep copy takes %8d", loop_time);
	/**/
}
void df::s_WorldManager::updateWithPre(unsigned int &fake_timeCounter)
{
	ObjectList2 ol = deletions;
	ObjectListIterator2	li = ObjectListIterator2(&ol);

	for (li.first(); !li.isDone(); li.next())
	{
		removeObject(li.currentObject());
	}            /// the only thing to do now is to delete the deletions objects from the updates.




// 	WorldFrameByTimeCounter fake_world = s_timeWarp::getInstance().getWorldFrameByTimeCounter(fake_timeCounter);
// 	ol = fake_world.getObjectList();
	ol = updates;   // should be the previous updates
	li = ObjectListIterator2(&ol);

	for (li.first(); !li.isDone(); li.next())
	{
		int x = li.currentObject()->getXVelocityStep();
		int y = li.currentObject()->getYVelocityStep();

		if (x != 0 || y != 0)   //? how to make sure did move? 
		{
			Position old_pos = li.currentObject()->getPosition();
			Position new_pos(old_pos.getX() + x, old_pos.getY() + y);

			if (moveObject(li.currentObject(), new_pos))
			{
				li.currentObject()->setPosition(new_pos);
			}
			//move Object to new pos;

		}
	}

	/*to do the deep copy while in the update*/

	/*s_timeWarp::getInstance().current_time_counter++;*/
	/**/
	//s_timeWarp::getInstance().deleteWorld(fake_timeCounter);
	//first delete the previous game world in order to avoid memory leak;
	WorldFrameByTimeCounter world_frame = s_timeWarp::getInstance().deepCopy(fake_timeCounter);
	
	s_timeWarp::getInstance().saveWorldFrame(world_frame);
	fake_timeCounter++;

	
}
int s_WorldManager::markForDeletion(s_Object *p_o)  // needs to check whether objects exist in the object list
{
	ObjectListIterator2 li = ObjectListIterator2(&deletions);
	while (!li.isDone())
	{
		if (li.currentObject() == p_o)
		{
			return 0;    // objects has been existed.
		}
		li.next();
	}
	deletions.insert(p_o);
	return 1;
}
ObjectList2 s_WorldManager::getAllObjects() const
{
	return updates;
}

void s_WorldManager::draw()
{
	ObjectList2 ol = updates;
	ObjectListIterator2 li(&ol);
	

	while (!li.isDone())
	{
		/*for (int alt = 0; alt < MAX_ALTITUDE; alt++)
		{
			s_Object *tem_obj = li.currentObject();
			if (tem_obj->getAltitude() == alt)    //  read exception thrown :: read access violation.
			{
				s_Box temp_box = s_Utility::getWorldBox(tem_obj);
				if (s_Utility::boxIntersectsBox(temp_box, view))
				{
					tem_obj->draw();
					
				}
				
			}
			li.next();
			
		}*/
		li.currentObject()->draw();
		li.next();
	}
	graphicsPacketCh g_packCh;
	g_packCh.color = S_COLOR_DEFAULT;
	g_packCh.content = ' ';
	g_packCh.x = 0;
	g_packCh.y = 0;
	g_packCh.len = sizeof(g_packCh);
	g_packCh.type = 2;  // end-flag
	s_NetworkManager::getInstance().df_send(static_cast<graphicsPacketCh *>(&g_packCh), g_packCh.len); // send end flag to client
	
}

ObjectList2 s_WorldManager::isCollision(s_Object *p_o, Position loc) const
{
	ObjectList2 collision_list;;

	ObjectListIterator2 li(&updates);

	for (li.first(); !li.isDone(); li.next())
	{
		s_Object *p_temp_obj = li.currentObject();

		if (p_temp_obj != p_o)
		{
			s_Box b = s_Utility::getWorldBox(p_o, loc);
			s_Box b_tmp = s_Utility::getWorldBox(p_temp_obj);

			if (s_Utility::boxIntersectsBox(b,b_tmp) && p_o->isSolid())
			{
				collision_list.insert(p_temp_obj);
			}
		}
	}
	return collision_list;

}

int s_WorldManager::moveObject(s_Object *p_o, Position loc)
{
	if (p_o->isSolid())
	{
		ObjectList2 list = isCollision(p_o, loc);
		if (!list.isEmpty())
		{
			bool do_move = true;

			ObjectListIterator2 li(&list);

			for (li.first(); !li.isDone(); li.next())
			{
				s_Object *p_temp_o = li.currentObject();

				s_EventCollision c(p_o, p_temp_o, loc);

				p_o->eventHandler(&c);

				p_temp_o->eventHandler(&c);

				if (p_o->isSolid() && p_temp_o->isSolid())
				{do_move = false;}
				

				if (do_move == false)
				{
					return 0;  // 0 for not move;
				}

			}
			
		}
	}

 	s_EventOut eo;
 	p_o->eventHandler(&eo);
 	p_o->setPosition(loc);
// 	if (p_view_following == p_o)
// 	{
// 		setViewPosition(p_o->getPosition()); // move the object and the view.
// 	}
	return 1;
}
s_WorldManager::~s_WorldManager()
{
}

void s_WorldManager::setBoundary(s_Box	new_boundary)
{
	boundary = new_boundary;
}
s_Box  s_WorldManager::getBoundary() const
{
	return boundary;
}
void  s_WorldManager::setView(s_Box new_view)
{
	view = new_view;
}
s_Box  s_WorldManager::getView() const
{
	return view;
}


void s_WorldManager::setViewPosition(Position view_pos)
{
	int x = view_pos.getX() - view.getHorizontal() / 2;
	if (x + view.getHorizontal() > boundary.getHorizontal())
	{
		x = boundary.getHorizontal() - view.getHorizontal();
	}
	if (x < 0)
	{
		x = 0;
	}


	//vertical

	int y = view_pos.getY() - view.getVertical() / 2;
	if (y + view.getVertical() > boundary.getVertical())
	{
		y = boundary.getVertical() - view.getVertical();
	}
	if (y < 0)
	{
		y = 0;
	}
	Position new_corner(x, y);
	view.setCorner(new_corner);
}

int s_WorldManager::setViewFollowing(s_Object *p_new_view_following)
{
	if (p_new_view_following == NULL)
	{
		return -1; // null
	}

	ObjectListIterator2 li = ObjectListIterator2(&updates);
	bool found = false;
	while (!li.isDone())
	{
		if (li.currentObject() == p_new_view_following)
		{
			found = true;
		}
	}
	if (found)
	{
		p_view_following = p_new_view_following;
		setViewPosition(p_view_following->getPosition());
		return 1;  // 1 for ok.
	}
	else return -2;  // -2 for object not found.
	p_view_following = p_new_view_following;
	
	
	//? how to set the view into window's center
}

int df::s_WorldManager::setUpdates(ObjectList2 new_updates)
{
	//needs to do the deep copy
	ObjectList2 object_copy;
	ObjectListIterator2 li(&new_updates);
	while (!li.isDone())
	{
		s_Object *objectTemp;
		objectTemp = li.currentObject()->clone();
		object_copy.insert(objectTemp);

		li.next();
	}
	this->updates = object_copy;
	return 0;
}

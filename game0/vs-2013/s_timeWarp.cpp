#include "s_timeWarp.h"
#include "Logmanager2.h"
#include "s_InputManager.h"
namespace df
{



	WorldFrameByTimeCounter * s_timeWarp::getAllWorldFrames()
	{
		return worldFrames;
	}

	int s_timeWarp::saveWorldFrame(WorldFrameByTimeCounter  world_frame)
	{
		unsigned int time_counter = world_frame.timeCounter;
		int index = time_counter % MAXTIMEWARP;   // put the index into loop from 0 to 299;
		worldFrames[index] = world_frame;
		//this->current_time_counter = time_counter;
		return 0;
	}

	WorldFrameByTimeCounter  df::s_timeWarp::deepCopy(unsigned int timeCounter)
	{
		WorldFrameByTimeCounter world_frame;
		world_frame.timeCounter = timeCounter;
		ObjectList2 object_original = s_WorldManager::getInstance().getAllObjects();
		ObjectListIterator2 object_li = ObjectListIterator2(&object_original);
		ObjectList2 object_copy;
		
		while (!object_li.isDone())
		{
			s_Object *objectTemp;
			objectTemp = object_li.currentObject()->clone();
			object_copy.insert(objectTemp);

			object_li.next();
			//delete objectTemp;  // for deleting the pointer 
		}
		world_frame.setObjectList(&object_copy);
		return world_frame;
	}   // return a whole world frame that includes the timeCounter and the objectList.

	WorldFrameByTimeCounter  df::s_timeWarp::getWorldFrameByTimeCounter(unsigned int timeCounter)
	{
		s_timeWarp &time_warp = s_timeWarp::getInstance();
		if (time_warp.current_time_counter - timeCounter >= MAXTIMEWARP)
		{
			LogManager2::getInstance().writeLog("time warp overflow...");
			//return NULL;
		}
		
		WorldFrameByTimeCounter world_frame = time_warp.worldFrames[timeCounter%MAXTIMEWARP];
		world_frame.timeCounter = timeCounter;
		return world_frame;
	}

	int s_timeWarp::deleteWorld(unsigned int timecounter)
	{
		delete(& (worldFrames[timecounter%MAXTIMEWARP]));
		return 0;
	}

	s_timeWarp & s_timeWarp::getInstance()
	{
		// TODO: insert return statement here

		static s_timeWarp * time_warp = NULL;

		if (!time_warp)
		{
			time_warp = new s_timeWarp;
		}
		return *time_warp;
	}

	int s_timeWarp::reApplyGameWorlds(WorldFrameByTimeCounter world_frame)
	{
		//set the world manager updates and fake time counter
		
		//s_WorldManager::getInstance().setUpdates(obj_warp);
		unsigned int fake_timeCounter = world_frame.timeCounter;
		//reapply the events and re-run the game till the actual time counter.
		unsigned int saved_timeCounter = this->current_time_counter;

		// the first thing to do is restoring the game world.

// 		WorldFrameByTimeCounter restore_world = getWorldFrameByTimeCounter(fake_timeCounter);
// 		ObjectList2 restore_li = restore_world.getObjectList();	
// 		s_WorldManager::getInstance().setUpdates(restore_li);

		fake_timeCounter++;  // next world
		while (fake_timeCounter <= saved_timeCounter && fake_timeCounter != world_frame.timeCounter)  // not the first time
		{
			LogManager2::getInstance().writeLog("re-run %d timeCounter", fake_timeCounter);
			s_WorldManager::getInstance().updateWithPre(fake_timeCounter);
			//s_InputManager::getInstance().getInput();
			// don't need to do events
			
		}
		WorldFrameByTimeCounter latest_world = getWorldFrameByTimeCounter(saved_timeCounter -1);
		ObjectList2 obj_warp = latest_world.getObjectList();
		ObjectListIterator2 li2 = df::ObjectListIterator2(&obj_warp);
		s_WorldManager::getInstance().setUpdates(obj_warp);
		return 0;   // 0 is success return value
	}

	s_timeWarp::s_timeWarp()
{
	current_time_counter = 0;
}


s_timeWarp::~s_timeWarp()
{
}
}
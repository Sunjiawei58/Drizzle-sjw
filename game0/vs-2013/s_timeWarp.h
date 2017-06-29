#pragma once
#ifndef S_TIME_WARP_H
#define S_TIME_WARP_H

#include "s_WorldManager.h"
#include "s_Object.h"
#include "s_Utility.h"
namespace df
{
	 class WorldFrameByTimeCounter
	{
	public:
		
		unsigned int timeCounter;
		void setObjectList(ObjectList2* objLi);
		ObjectList2 getObjectList() const;
	private:
		ObjectList2 objects;
	};
	const int MAXTIMEWARP = 500;   // 
	class s_timeWarp
	{
	public:
		bool timeWarpOn = true;
		unsigned int current_time_counter;
		WorldFrameByTimeCounter worldFrames[MAXTIMEWARP];
		WorldFrameByTimeCounter* getAllWorldFrames();
		int saveWorldFrame(WorldFrameByTimeCounter world_frame);
		WorldFrameByTimeCounter deepCopy(unsigned int timeCounter);    // this is for deepCopy
		WorldFrameByTimeCounter  getWorldFrameByTimeCounter(unsigned int timeCounter);   // get frame Objects by timeCounter
		int deleteWorld(unsigned int timecounter);
		static s_timeWarp& getInstance();  // singleton

		int reApplyGameWorlds(WorldFrameByTimeCounter world_frame);
	private:
		s_timeWarp(s_timeWarp const&);  // don't allow copy
		void operator=(s_timeWarp const&);  //don't allow assignment.
		s_timeWarp();
		~s_timeWarp();
	};

}
#endif;
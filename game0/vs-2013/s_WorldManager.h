#ifndef S_WORLDMANAGER_H
#define S_WORLDMANAGER_H
#include "ObjectList2.h"
#include "s_Object.h"
#include "s_Manager.h"
namespace df
{


	class s_WorldManager : public s_Manager
	{
	private:
		s_WorldManager();
		s_WorldManager(s_WorldManager const&);  // don't allow copy
		void operator=(s_WorldManager const&);  //don't allow assignment.

		ObjectList2 updates;
		ObjectList2 deletions;
		
		//extension for view
		s_Box boundary;
		s_Box view;

		s_Object *p_view_following;
	public:
		  // solid object

		static s_WorldManager &getInstance();

		int startUp();  // Startup game world (initalize everything to empty)
		void shutDown(); // shutdown game world (delete all game world objects)
		
		int insertObject(s_Object *p_o);  // ok return 1; else return 0;
		int removeObject(s_Object *p_o);   // ok return 1; else return 0;

		ObjectList2 getAllObjects() const;

		void update();  // update game world, delete objects marked for deletion

		void updateWithPre(unsigned int &fake_timeCounter);

		int markForDeletion(s_Object *p_o);
		~s_WorldManager();

		void draw();

		ObjectList2 isCollision(s_Object *p_o, Position loc) const;

		int moveObject(s_Object *p_o, Position loc); 

		void setBoundary(s_Box	new_boundary);
		s_Box getBoundary() const;
		void setView(s_Box new_view);
		s_Box getView() const;

		void setViewPosition(Position view_pos);

		int setViewFollowing(s_Object *p_new_view_following);

		int setUpdates(ObjectList2 new_updates);
	};
}
#endif
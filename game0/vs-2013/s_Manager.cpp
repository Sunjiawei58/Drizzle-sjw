#include "s_Manager.h"
#include <string>
#include "s_WorldManager.h"
using namespace df;

s_Manager::s_Manager()
{
}


s_Manager::~s_Manager()
{
}
void s_Manager::setType(std::string type)
{
	this->type = type;
}
bool s_Manager::isStarted() const
{
	if(is_started == true) 
		return true;	
	else return false;
	
}
int s_Manager::onEvent(const s_Event*p_e) const    // counld support step events.
{
	int count = 0;

	ObjectList2 obj = s_WorldManager::getInstance().getAllObjects();
	ObjectListIterator2 li = ObjectListIterator2(&obj);

	while (!li.isDone())
	{
		li.currentObject()->eventHandler(p_e);    // handle event with every objects(interest considered later)
		li.next();
		count++;
	}
	return count;
}
int s_Manager::startUp()
{
	is_started = true;   // set the flag to true;
	return 1;   // for success
}
void s_Manager::shutDown()
{

}
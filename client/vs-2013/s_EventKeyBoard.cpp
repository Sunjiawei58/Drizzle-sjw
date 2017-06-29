#include "s_EventKeyBoard.h"

using namespace df;
s_EventKeyBoard::s_EventKeyBoard()
{
	
}
void s_EventKeyBoard::setKey(Input::Key new_key)
{
	key_val = new_key;
}

Input::Key s_EventKeyBoard::getKey() const
{
	return key_val;
}

void s_EventKeyBoard::setKeyboardAction(EventKeyboardAction new_action)
{
	keyboard_action = new_action;
}
EventKeyboardAction s_EventKeyBoard::getKeyboardAction() const
{
	return keyboard_action;
}
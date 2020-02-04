#include "KeyEvent.h"

KeyEvent::KeyEvent(const Key & code)
	:Event(KEY_EVENT)
	,mKey(code)
{
}

KeyEvent::~KeyEvent()
{
}

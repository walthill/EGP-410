#include "MouseEvent.h"

MouseEvent::MouseEvent()
{
	mType = INVALID_EVENT_TYPE;
}


MouseEvent::MouseEvent(EventType type, int mouseX, int mouseY)
{
	mType = type;
	mX = mouseX;
	mY = mouseY;
}

MouseEvent::~MouseEvent()
{
}

/*void MouseEvent::setEvent(EventType type, int mouseX, int mouseY)
{
	mType = type;
	mX = mouseX;
	mY = mouseY;
}*/


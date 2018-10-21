#ifndef MOUSE_EVENT_H
#define MOUSE_EVENT_H

#include <string>
#include <trackable.h>
#include "Event.h"

using namespace std;

class MouseEvent: public Event
{
public:
	MouseEvent();
	MouseEvent(EventType type, int mouseX, int mouseY);
	virtual ~MouseEvent();

	void setEvent(EventType type, int mouseX, int mouseY);
	
	int getX() const { return mX; };
	int getY() const { return mY; }

private:
	int mX, mY;

};

#endif // !MOUSE_EVENT_H

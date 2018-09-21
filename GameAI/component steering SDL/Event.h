#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <trackable.h>

using namespace std;

enum EventType
{
	INVALID_EVENT_TYPE = -1,
	KEY_DOWN_EVENT,
	MOUSE_DOWN_EVENT, //Input system events
	ESC,
	SPAWN,
	DELETE_UNIT,
	MOVE_PLAYER,
	QUIT,
	MOUSE_MOTION,
	DEVICE_ADDED_OR_REMOVED,
	UNDEFINED,
	
	NUM_EVENT_TYPES //Tracks the number of event types
};

const string EVENT_NAMES[NUM_EVENT_TYPES] = {	
	"Key Down Event",											
	"Mouse Down Event",
	"Escape Key Event",
	"Spawn Event",
	"delete event",
	"move event",
	"quit",
	"removed/added device",
	"NULL"
};

class Event:public Trackable
{
public:
	Event();
	Event( EventType type );
	virtual ~Event();

	void setType(EventType type);
	EventType getType() const { return mType; };
	const string& getEventName() const;

protected:
	EventType mType;
};

#endif // !EVENT_H

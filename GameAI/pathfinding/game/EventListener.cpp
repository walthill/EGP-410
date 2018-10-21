#include "EventListener.h"
#include "EventSystem.h"


EventListener::EventListener(EventSystem* pEventSystem)
{
}

EventListener::~EventListener()
{
		if(EventSystem::hasInstance())
			EventSystem::getInstance()->removeListenerFromAllEvents(this);
}

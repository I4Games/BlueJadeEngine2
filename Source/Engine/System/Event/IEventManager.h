#pragma once
#include <string>
#include "FastDelegate.h"
#include "EventData\IEventData.h"

typedef fastdelegate::FastDelegate1<IEventData*> EventListenerDelegate;

class IEventManager {
public:
	enum eConstants { kINFINITE = 0xffffffff };
	virtual ~IEventManager(void) {};

	virtual bool VAddListener(const EventListenerDelegate& eventDelegate, const EventType& type) = 0;
	virtual bool VRemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type) = 0;
	virtual bool VQueueEvent(IEventData* pEvent) = 0;
	virtual bool VTriggerEvent(IEventData* pEvent) const = 0;
	virtual bool VAbortEvent(const EventType& type, bool allOfType = false) = 0;
	virtual bool VUpdate(unsigned long maxMillis = kINFINITE) = 0;
};
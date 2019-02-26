#pragma once
#include "IEventManager.h"
#include <list>
#include <map>

const unsigned int EVENTMANAGER_NUM_QUEUES = 2;
class EventManager : public IEventManager {
	typedef std::list<EventListenerDelegate> EventListenerList;
	typedef std::map<EventType, EventListenerList> EventListenerMap;
	typedef std::list<IEventData*> EventQueue;

	EventListenerMap m_eventListeners;
	EventQueue m_queues[EVENTMANAGER_NUM_QUEUES];
	int m_activeQueue;

	static EventManager* m_instance;

public:
	virtual ~EventManager(void) { }

	virtual bool VAddListener(const EventListenerDelegate& eventDelegate, const EventType& type);
	virtual bool VRemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type);
	virtual bool VQueueEvent(IEventData* pEvent);
	virtual bool VTriggerEvent(IEventData* pEvent) const;
	virtual bool VAbortEvent(const EventType& type, bool allOfType = false);
	virtual bool VUpdate(unsigned long maxMillis = kINFINITE);

	static EventManager* GetInstance(void) {
		if (!m_instance) {
			m_instance = new EventManager();
		}
		return m_instance;
	}
};

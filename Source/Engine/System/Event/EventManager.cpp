#include "EventManager.h"
#include <iostream>
#include <Windows.h>

EventManager* EventManager::m_instance = 0;

bool EventManager::VAddListener(const EventListenerDelegate& eventDelegate, const EventType& type) {
	EventListenerList& eventListenerList = m_eventListeners[type];

	for (auto it = eventListenerList.begin(); it != eventListenerList.end(); ++it) {
		if (eventDelegate == (*it)) {
			std::cout << "WARNING: Attempting to double-register a delegate" << std::endl;
			return false;
		}
	}
	eventListenerList.push_back(eventDelegate);
	return true;
}

bool EventManager::VRemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type) {
	auto findIt = m_eventListeners.find(type);

	if (findIt != m_eventListeners.end()) {
		EventListenerList& listeners = findIt->second;
		for (auto it = listeners.begin(); it != listeners.end(); ++it) {
			if (eventDelegate == (*it)) {
				listeners.erase(it);
				return true;
			}
		}
	}

	return false;
}

bool EventManager::VQueueEvent(IEventData* pEvent) {
	if (m_activeQueue < 0 || m_activeQueue >= EVENTMANAGER_NUM_QUEUES) {
		std::cout << ("ERROR: Active queue index out of bounds") << std::endl;
		return false;
	}

	auto findIt = m_eventListeners.find(pEvent->VGetEventType());
	if (findIt != m_eventListeners.end()) {
		m_queues[m_activeQueue].push_back(pEvent);
		return true;
	}else {
		return false;
	}
}

bool EventManager::VAbortEvent(const EventType& inType, bool AllOfType) {
	bool success = false;

	if (m_activeQueue < 0 || m_activeQueue >= EVENTMANAGER_NUM_QUEUES) {
		std::cout << ("ERROR: Active queue index out of bounds") << std::endl;
		return false;
	}

	auto findIt = m_eventListeners.find(inType);
	if (findIt != m_eventListeners.end()) {
		EventQueue& eventQueue = m_queues[m_activeQueue];
		auto it = eventQueue.begin();
		while (it != eventQueue.end()) {
			auto thisIt = it;
			++it;
			if ((*thisIt)->VGetEventType() == inType) {
				eventQueue.erase(thisIt);
				success = true;
				if (!AllOfType) {
					return true;
				}
			}
		}
	}

	return success;
}

bool EventManager::VUpdate(unsigned long maxMillis) {
	unsigned long currMs = GetTickCount();
	unsigned long maxMs = ((maxMillis == IEventManager::kINFINITE) ?
		(IEventManager::kINFINITE) : (currMs + maxMillis));

	int queueToProcess = m_activeQueue;
	m_activeQueue = (m_activeQueue + 1) % EVENTMANAGER_NUM_QUEUES;
	m_queues[m_activeQueue].clear();

	while (!m_queues[queueToProcess].empty()) {
		IEventData* pEvent = m_queues[queueToProcess].front();
		m_queues[queueToProcess].pop_front();
		const EventType& eventType = pEvent->VGetEventType();
		auto findIt = m_eventListeners.find(eventType);
		if (findIt != m_eventListeners.end()) {
			const EventListenerList& eventListeners = findIt->second;
			for (auto it = eventListeners.begin(); it != eventListeners.end(); ++it) {
				EventListenerDelegate listener = (*it);
				listener(pEvent);
			}
		}

		currMs = GetTickCount();
		if (maxMillis != IEventManager::kINFINITE && currMs >= maxMs) {
			break;
		}
	}

	bool queueFlushed = (m_queues[queueToProcess].empty());
	if (!queueFlushed) {
		while (!m_queues[queueToProcess].empty()) {
			IEventData* pEvent = m_queues[queueToProcess].back();
			m_queues[queueToProcess].pop_back();
			m_queues[m_activeQueue].push_front(pEvent);
		}
	}

	return queueFlushed;
}

bool EventManager::VTriggerEvent(IEventData* pEvent) const{
	auto findIt = m_eventListeners.find(pEvent->VGetEventType());
	if (findIt != m_eventListeners.end()) {
		for (auto it = (*findIt).second.begin(); it != (*findIt).second.end(); ++it) {
			(*it)(pEvent);
		}
		return true;
	}

	return false;
}
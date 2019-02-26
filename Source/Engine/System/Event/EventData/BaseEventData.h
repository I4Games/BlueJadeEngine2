#pragma once
#include "IEventData.h"

class BaseEventData : public IEventData {
	const float m_timeStamp;
public:
	explicit BaseEventData(const float timeStamp = 0.0f) : m_timeStamp(timeStamp) {}
	virtual ~BaseEventData(void) {}

	virtual const EventType& VGetEventType(void) const = 0;
	float VGetTimeStamp(void) const { return m_timeStamp; }
};
#pragma once
#include <ostream>

typedef unsigned long EventType;

class IEventData {
public:
	virtual const EventType& VGetEventType(void) const = 0;
	virtual float VGetTimeStamp(void) const = 0;
	virtual const std::string GetName(void) const = 0;
};
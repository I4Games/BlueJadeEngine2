#pragma once
#include "BaseEventData.h"

class EvtData_Keydown : public BaseEventData {
	unsigned const int m_keyCode;
public:
	static const EventType sk_EventType;
	explicit EvtData_Keydown(unsigned const int keyCode) : m_keyCode(keyCode) { }
	virtual const EventType& VGetEventType(void) const { return sk_EventType; }
	virtual const std::string GetName(void) const { return "EvtData_Keydown"; }
	unsigned const int GetKeyCode(void) const { return m_keyCode; }
};
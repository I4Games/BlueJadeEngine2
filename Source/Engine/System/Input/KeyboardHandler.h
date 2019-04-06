#include "InputInterfaces.h"
#include <string>
#include <iostream>
#include <map>
#include "../Event/EventData/EvtData_Keydown.h"
#include "../Event/EventManager.h"

struct KeyState {
	bool pressed;
	bool thisFrame;
};

class KeyboardHandler:public IKeyboardHandler 
{
public:

	std::map<unsigned int, KeyState> keyMap;

	virtual bool VOnKeyDown(unsigned int const kcode)
	{
		EvtData_Keydown* pEvent = new EvtData_Keydown(kcode);
		EventManager::GetInstance()->VQueueEvent(pEvent);

		auto it = keyMap.find(kcode);

		if (it == keyMap.end()) {
			keyMap[kcode] = KeyState();
		}
		keyMap[kcode].pressed = true;
		keyMap[kcode].thisFrame = true;

		return true;
	}

	virtual bool VIsKeyDown(unsigned int const kcode) {
		auto it = keyMap.find(kcode);

		if (it != keyMap.end()) {
			return keyMap[kcode].pressed && keyMap[kcode].thisFrame;
		}
		return false;
	}

	virtual bool VOnKeyUp(unsigned int const kcode)
	{
		keyMap[kcode].pressed = false;
		keyMap[kcode].thisFrame = true;
		return true;
	}

	virtual bool VIsKeyPressed(unsigned int const kcode) {
		auto it = keyMap.find(kcode);

		if (it != keyMap.end()) {
			return keyMap[kcode].pressed;
		}
		return false;
	}

	virtual void VUpdate() {
		for (auto it = keyMap.begin(); it != keyMap.end(); ++it) {
			(*it).second.thisFrame = false;
		}
	}
};
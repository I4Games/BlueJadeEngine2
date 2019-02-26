#include "InputInterfaces.h"
#include <string>
#include <iostream>
#include "../Event/EventData/EvtData_Keydown.h"
#include "../Event/EventManager.h"


class KeyboardHandler:public IKeyboardHandler 
{
	bool VOnKeyDown(unsigned int const kcode)
	{
		EvtData_Keydown* pEvent = new EvtData_Keydown(kcode);
		EventManager::GetInstance()->VQueueEvent(pEvent);
		return true;
	}

	bool VOnKeyUp(unsigned int const kcode)
	{
		return true;
	}

};
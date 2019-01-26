#pragma once
#include "InputInterfaces.h"
#include "KeyboardHandler.h"

class InputManager {
public:
	IKeyboardHandler* m_keyboardHandler;
	IPointerHandler* m_pointerHandler;
	//IJoystickHandler* m_joystickHandler;
	//IGamepadHandler* m_gamepadHandler;

	InputManager() 
	{
		m_keyboardHandler = new KeyboardHandler();
	}
};
#pragma once
#include "InputInterfaces.h"
#include "KeyboardHandler.h"

class InputManager {
	static InputManager* m_instance;
public:
	IKeyboardHandler* m_keyboardHandler;
	IPointerHandler* m_pointerHandler;
	//IJoystickHandler* m_joystickHandler;
	//IGamepadHandler* m_gamepadHandler;

	InputManager(){
		m_keyboardHandler = new KeyboardHandler();
	};

	void KeyDown(unsigned const int kcode) {
		m_keyboardHandler->VOnKeyDown(kcode);
	}

	static InputManager* GetInstance() {
		if (!m_instance) {
			m_instance = new InputManager();
		}
		return m_instance;
	}
};

InputManager* InputManager::m_instance = 0;
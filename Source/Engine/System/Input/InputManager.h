#pragma once
#include "InputInterfaces.h"
#include "KeyboardHandler.h"

class InputManager {
	static InputManager* m_instance;
public:
	static InputManager* GetInstance();

	IKeyboardHandler* m_keyboardHandler;
	IPointerHandler* m_pointerHandler;
	//IJoystickHandler* m_joystickHandler;
	//IGamepadHandler* m_gamepadHandler;

	InputManager();

	void KeyDown(unsigned const int kcode);
	void KeyUp(unsigned const int kcode);

	bool IsKeyDown(unsigned const int kcode);
	bool IsKeyPressed(unsigned const int kcode);

	void Update();
};
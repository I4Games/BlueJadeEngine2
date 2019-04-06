#include "InputManager.h"

InputManager* InputManager::m_instance = 0;

InputManager* InputManager::GetInstance() {
	if (!m_instance) {
		m_instance = new InputManager();
	}
	return m_instance;
}

InputManager::InputManager() {
	m_keyboardHandler = new KeyboardHandler();
}

void InputManager::KeyDown(unsigned const int kcode) {
	m_keyboardHandler->VOnKeyDown(kcode);
}

void InputManager::KeyUp(unsigned const int kcode) {
	m_keyboardHandler->VOnKeyUp(kcode);
}

bool InputManager::IsKeyDown(unsigned const int kcode) {
	return m_keyboardHandler->VIsKeyDown(kcode);
}

bool InputManager::IsKeyPressed(unsigned const int kcode) {
	return m_keyboardHandler->VIsKeyPressed(kcode);
}

void InputManager::Update() {
	m_keyboardHandler->VUpdate();
}
#include "BaseComponent.h"

GameObject* BaseComponent::GetGameObject() {
	return gameObject;
}

void BaseComponent::SetGameObject(GameObject* gameObject) {
	this->gameObject = gameObject;
}
#include "GameObjectManager.h"

GameObjectManager::GameObjectManager() {
	std::string name = "";
	rootScene = new GameObject(name);
}

GameObjectManager::~GameObjectManager() {
	delete rootScene;
}

GameObject* GameObjectManager::GetGameObjectByName(std::string &name) {
	return rootScene->FindChildByName(name);
}
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

void GameObjectManager::AddGameObject(GameObject* gameObject, GameObject* parent) {
	if (parent) {
		parent->AddChild(gameObject);
	}else {
		rootScene->AddChild(gameObject);
		gameObject->SetParent(NULL);
	}
}
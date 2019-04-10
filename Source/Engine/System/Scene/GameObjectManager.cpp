#include "GameObjectManager.h"

GameObjectManager* GameObjectManager::Instance = 0;

GameObjectManager* GameObjectManager::GetInstance() {
	if (!Instance) {
		Instance = new GameObjectManager();
	}
	return Instance;
}

GameObjectManager::GameObjectManager() {
	std::string name = "";
	rootScene = new GameObject(name);
}

GameObjectManager::~GameObjectManager() {
	delete rootScene;
}

void GameObjectManager::SetRootGameObject(GameObject* newRoot) {
	GameObject* oldRoot = GameObjectManager::GetInstance()->rootScene;
	GameObjectManager::GetInstance()->rootScene = newRoot;

	if(oldRoot) delete oldRoot;
}

void GameObjectManager::EmptyRoot() {
	std::vector<GameObject*> root = GameObjectManager::GetInstance()->rootScene->GetChildren();
	for (auto it = root.begin(); it != root.end(); ++it) {
		delete (*it);
	}
	root.clear();
}

GameObject* GameObjectManager::GetGameObjectByName(std::string &name) {
	return rootScene->FindChildByName(name);
}

void GameObjectManager::AddGameObject(GameObject* gameObject, GameObject* parent) {
	if (parent && parent != rootScene) {
		parent->AddChild(gameObject);
	}else {
		rootScene->AddChild(gameObject);
		gameObject->SetParent(NULL);
	}
}

void GameObjectManager::DestroyGameObject(GameObject* gameObject) {
	if (gameObject->GetParent() != nullptr) {
		std::vector<GameObject*>& siblings = gameObject->GetParent()->GetChildren();
		siblings.erase(std::remove(siblings.begin(), siblings.end(), gameObject), siblings.end());
	}
	else {
		std::vector<GameObject*>& roots = rootScene->GetChildren();
		roots.erase(std::remove(roots.begin(), roots.end(), gameObject), roots.end());
	}

	delete gameObject;
}
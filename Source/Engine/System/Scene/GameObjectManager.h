#pragma once

#include "GameObject.h"

class GameObjectManager {
public:
	static GameObjectManager* GetInstance();

	GameObjectManager();
	~GameObjectManager(void);
	GameObject* GetRootGameObject() { return rootScene; }
	void SetRootGameObject(GameObject* newRoot);
	void EmptyRoot();
	GameObject* GetGameObjectByName(std::string &name);
	void AddGameObject(GameObject* gameObject, GameObject* parent);

	void Update(float msec) { rootScene->Update(msec); }

protected:
	static GameObjectManager* Instance;

	GameObject* rootScene;
};
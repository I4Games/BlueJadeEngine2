#pragma once

#include "GameObject.h"
#include <vector>

class GameObjectManager {
public:
	static GameObjectManager* GetInstance();

	GameObjectManager();
	~GameObjectManager(void);
	GameObject* GetRootGameObject() { return rootScene; }
	void SetRootGameObject(GameObject* newRoot);
	void EmptyRoot();
	GameObject* GetGameObjectByName(std::string &name);
	std::vector<GameObject*> GetGameObjectsByName(std::string name);
	void AddGameObject(GameObject* gameObject, GameObject* parent);
	void DestroyGameObject(GameObject* gameObject);

	void Init() { rootScene->Init(); }
	void Update(float msec) { rootScene->Update(msec); }

protected:
	static GameObjectManager* Instance;

	GameObject* rootScene;
};
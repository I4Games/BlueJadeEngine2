#pragma once

#include "GameObject.h"

class GameObjectManager {
public:
	GameObjectManager();
	~GameObjectManager(void);
	GameObject* GetRootGameObject() { return rootScene; }
	GameObject* GetGameObjectByName(std::string &name);

protected:
	GameObject* rootScene;
};
#pragma once
#include "GameObject.h"
#include <string>
#include <stack>
#include "tinyxml2.h"

#include "Component\TransformComponent.h"
#include "Component\PhysicsRBody.h"
#include "Component\SpriteRenderer.h"
#include "Component\AudioPlayer.h"

class SceneManager {
public:
	static SceneManager* GetInstance();
	static BaseComponent* MakeComponent(ComponentType cType);

	//Members

	//Methods
	void BuildScene(std::string xmlFilename);

private:
	static SceneManager* Instance;
	static std::string assetRoot;

	//Members
	std::stack<GameObject*> parentStack;

	//Methods
	void AddGameObject(tinyxml2::XMLNode* node, GameObject* parent);
	void AddComponent(GameObject* obj, tinyxml2::XMLElement* elem);
};
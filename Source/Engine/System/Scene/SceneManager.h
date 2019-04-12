#pragma once
#include "GameObject.h"
#include <string>
#include <stack>
#include "tinyxml2.h"

class SceneManager {
public:
	static SceneManager* GetInstance();
	static BaseComponent* MakeComponent(ComponentType cType);

	//Members
	std::string ScenePath = "../Assets/Scenes/";
	std::string nextScene;
	bool pendingSceneChange = false;

	//Methods
	void BuildScene(std::string xmlFilename);
	void RequestSceneChange(std::string levelName);
	void Update();

private:
	static SceneManager* Instance;
	static std::string assetRoot;

	//Members
	std::stack<GameObject*> parentStack;

	//Methods
	void AddGameObject(tinyxml2::XMLNode* node, GameObject* parent);
	void AddComponent(GameObject* obj, tinyxml2::XMLElement* elem);
	
};
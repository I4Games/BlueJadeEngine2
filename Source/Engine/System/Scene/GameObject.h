#ifndef BLUEJADE_GAMEOBJECT
#define BLUEJADE_GAMEOBJECT

#include <vector>
#include <SFML/Graphics.hpp>

using namespace sf;

class BaseComponent;
class TransformComponent;

class GameObject {
public:
	GameObject(std::string &name);
	~GameObject(void);

	TransformComponent* GetTransform();
	std::string GetName();
	GameObject* GetParent();
	
	void SetParent(GameObject* p);
	void AddChild(GameObject* s);
	void AddComponent(BaseComponent* c);

	GameObject* FindChildByName(std::string &name);

	virtual void Update(float msec);

protected:
	GameObject* parent;
	std::string name;
	TransformComponent* transform;
	std::vector<GameObject*> children;
	std::vector<BaseComponent*> components;
};

#endif
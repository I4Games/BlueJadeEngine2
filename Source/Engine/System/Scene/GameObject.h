#ifndef BLUEJADE_GAMEOBJECT
#define BLUEJADE_GAMEOBJECT

#include <vector>
#include <SFML/Graphics.hpp>

using namespace sf;

class BaseComponent;
class TransformComponent;

enum ComponentType {
	C_Transform,
	C_SpriteRenderer,
	C_PhysicsRBody
};

class GameObject {
public:
	GameObject(std::string &name);
	~GameObject(void);

	Transform& GetTransform();
	TransformComponent* GetTransformComponent();
	std::string GetName();
	GameObject* GetParent();
	
	void SetParent(GameObject* p);
	void AddChild(GameObject* s);
	void AddComponent(BaseComponent* c);

	GameObject* FindChildByName(std::string &name);

	BaseComponent* GetComponent(ComponentType cType);

	virtual void Update(float msec);

protected:
	GameObject* parent;
	std::string name;
	TransformComponent* transform;
	std::vector<GameObject*> children;
	std::vector<BaseComponent*> components;
};

#endif

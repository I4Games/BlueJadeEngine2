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
	C_PhysicsRBody,
	C_AudioPlayer
};

class GameObject {
public:
	GameObject(std::string &name);
	~GameObject(void);

	Transform& GetTransform();
	Transform& GetWorldTransform();
	TransformComponent* Transform();
	std::string GetName();
	GameObject* GetParent();
	std::vector<GameObject*> GetChildren() { return children; }
	
	void SetParent(GameObject* p);
	void AddChild(GameObject* s);
	void AddComponent(BaseComponent* c);

	void Translate(sf::Vector2f t);
	void Rotate(float r);
	void Scale(sf::Vector2f s);

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

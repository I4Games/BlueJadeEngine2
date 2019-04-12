#ifndef BLUEJADE_GAMEOBJECT
#define BLUEJADE_GAMEOBJECT

#include <vector>
#include <SFML/Graphics.hpp>
#include "../Physics/PhysicsSystem.h"

using namespace sf;

class BaseComponent;
class TransformComponent;

enum ComponentType {
	C_Transform,
	C_SpriteRenderer,
	C_TextRenderer,
	C_PhysicsRBody,
	C_AudioPlayer,
	C_Script,
	C_Paddle,
	C_Ball,
	C_ArkanoidManager
};

class GameObject {
public:
	GameObject(std::string &name);
	~GameObject(void);

	Transform& GetTransform();
	Transform& GetWorldTransform();
	TransformComponent* Transform();
	std::string GetName();
	std::string GetTag();
	GameObject* GetParent();
	std::vector<GameObject*>& GetChildren() { return children; }
	std::vector<BaseComponent*>& GetComponents() { return components; }
	
	void SetParent(GameObject* p);
	void AddChild(GameObject* s);
	void AddComponent(BaseComponent* c);
	void SetTag(std::string newTag);

	void Translate(sf::Vector2f t);
	void Rotate(float r);
	void Scale(sf::Vector2f s);

	void RemoveChildren();

	GameObject* FindChildByName(std::string &name);

	BaseComponent* GetComponent(ComponentType cType);

	virtual void Update(float msec);

	//Events
	virtual void OnCollisionDetected(GameObject* other, CollisionSide side);

protected:
	GameObject* parent;
	std::string name;
	std::string tag;
	TransformComponent* transform;
	std::vector<GameObject*> children;
	std::vector<BaseComponent*> components;
};

#endif

#ifndef BLUEJADE_BASECOMPONENT
#define BLUEJADE_BASECOMPONENT

#include "../../Physics/PhysicsSystem.h"

class GameObject;
enum ComponentType;

class BaseComponent {
public:
	virtual ~BaseComponent() {};

	GameObject* GetGameObject();
	void SetGameObject(GameObject* gameObject);

	virtual void Update(float msec) = 0;
	virtual void Init() = 0;
	virtual void OnCollisionDetected(GameObject* other, CollisionSide side) {}
	virtual ComponentType GetComponentType() = 0;

protected:
	GameObject* gameObject;
};

#endif
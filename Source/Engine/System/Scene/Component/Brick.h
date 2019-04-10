#pragma once
#include "BaseComponent.h"
#include "PhysicsRBody.h"

class Brick : public BaseComponent {
public:
	PhysicsRBody* rbody;

	//Base Component
	virtual ComponentType GetComponentType();
	virtual void Init();
	virtual void Update(float msec);

	//Events
	virtual void OnCollisionDetected(GameObject* other, CollisionSide side);
};
#pragma once
#include "BaseComponent.h"
#include "PhysicsRBody.h"

class Paddle : public BaseComponent {
public:
	float speed;
	PhysicsRBody* rbody;

	//Base Component
	virtual ComponentType GetComponentType();
	virtual void Init();
	virtual void Update(float msec);

	//Events
	virtual void OnCollisionDetected(GameObject* other, CollisionSide side);
};
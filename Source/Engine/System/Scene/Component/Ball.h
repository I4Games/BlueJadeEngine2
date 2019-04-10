#pragma once
#include "BaseComponent.h"
#include "PhysicsRBody.h"


class Ball : public BaseComponent {
protected:
	float xDir;
	float yDir;

public:
	float speed;
	PhysicsRBody* rbody;
	float initialAngle;

	//Base Component
	virtual ComponentType GetComponentType();
	virtual void Init();
	virtual void Update(float msec);

	//Events
	virtual void OnCollisionDetected(GameObject* other, CollisionSide side);
};
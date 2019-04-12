#pragma once
#include "BaseComponent.h"
#include "PhysicsRBody.h"
#include "AudioPlayer.h"
#include <SFML/Graphics.hpp>

class Ball : public BaseComponent {
protected:
	float xDir;
	float yDir;

public:
	float speed;
	PhysicsRBody* rbody;
	float initialAngle;
	AudioPlayer* audioPlayer;
	sf::Vector2f originalPosition;

	//Base Component
	virtual ComponentType GetComponentType();
	virtual void Init();
	virtual void Update(float msec);

	//Events
	virtual void OnCollisionDetected(GameObject* other, CollisionSide side);
};
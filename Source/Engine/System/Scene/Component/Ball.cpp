#include "Ball.h"
#include "../GameObject.h"
#include "TransformComponent.h"
#include "../../Input/InputManager.h"
#include "../../Graphics/GraphicsSystem.h"
#include "../GameObjectManager.h"
#include "ArkanoidManager.h"
#include "TransformComponent.h"

#include <SFML/Graphics.hpp>

ComponentType Ball::GetComponentType() {
	return C_Ball;
}

void Ball::Init() {
	rbody = (PhysicsRBody*)(gameObject->GetComponent(C_PhysicsRBody));
	xDir = cos(initialAngle * 3.14f / 180.f);
	yDir = -sin(initialAngle * 3.14f / 180.f);

	audioPlayer = (AudioPlayer*)gameObject->GetComponent(C_AudioPlayer);
	originalPosition = gameObject->Transform()->GetPosition();
}

void Ball::Update(float msec) {
	sf::Vector2f pos = gameObject->Transform()->GetPosition();
	float width = GraphicsSystem::GetInstance()->WindowWidth;
	float height = GraphicsSystem::GetInstance()->WindowHeight;

	if ((pos.x > width && xDir > 0.f) || (pos.x < 0 && xDir < 0.f)) {
		xDir *= -1.f;
	}else if ((pos.y < 0 && yDir < 0.f)) {
		yDir *= -1.f;
	}
	else if (pos.y > height && yDir > 0.f) {
		gameObject->Transform()->SetPosition(originalPosition);
		yDir = -1.f;
		ArkanoidManager::GetInstance()->OnLifeLost();
	}

	rbody->currentVelocity.x = xDir * speed;
	rbody->currentVelocity.y = yDir * speed;
}

void Ball::OnCollisionDetected(GameObject* other, CollisionSide side) {
	
	if (other->GetName() == "Paddle" || other->GetName() == "Brick") {
		switch (side) {
			case Up:
			case Down:
				yDir *= -1;
				break;
			case Left:
			case Right:
				xDir *= -1;
				break;
		}

		if (other->GetName() == "Brick") {
			GameObjectManager::GetInstance()->DestroyGameObject(other);
			ArkanoidManager::GetInstance()->OnBrickDestroyed();
		}else {
			audioPlayer->PlaySound();
		}
	}
}
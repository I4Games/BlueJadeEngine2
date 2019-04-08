#include "Paddle.h"
#include "../GameObject.h"
#include "../../Input/InputManager.h"
#include <SFML/Graphics.hpp>

ComponentType Paddle::GetComponentType() {
	return C_Paddle;
}

void Paddle::Init() {
	rbody = (PhysicsRBody*)(gameObject->GetComponent(C_PhysicsRBody));
}

void Paddle::Update(float msec) {

	float xDir = 0.0f;
	if (InputManager::GetInstance()->IsKeyPressed(sf::Keyboard::Right)) {
		xDir = 1.0f;
	}else if (InputManager::GetInstance()->IsKeyPressed(sf::Keyboard::Left)) {
		xDir = -1.0f;
	}

	rbody->currentVelocity.x = speed * xDir * (msec * 1000);
}

void Paddle::OnCollisionDetected(GameObject* other) {

}
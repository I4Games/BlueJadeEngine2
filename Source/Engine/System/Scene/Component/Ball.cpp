#include "Ball.h"
#include "../GameObject.h"
#include "../../Input/InputManager.h"
#include <SFML/Graphics.hpp>

ComponentType Ball::GetComponentType() {
	return C_Ball;
}

void Ball::Init() {
	rbody = (PhysicsRBody*)(gameObject->GetComponent(C_PhysicsRBody));
}

void Ball::Update(float msec) {
	float xDir = 1.0f;
	float yDir = -1.0f;

	rbody->Integrate(msec);


	if (InputManager::GetInstance()->IsKeyPressed(sf::Keyboard::Space)) {
		rbody->AddForce(Vector2f(150.0f, -700.0f));
		//rbody ->currentVelocity.y = speed * yDir * (msec * 1000);
	}
}

void Ball::OnCollisionDetected(GameObject* other) {
	
	if (other->GetName() == "Paddle") {
		std::cout << " hit Paddle ";
	}
	if (other->GetName() == "Brick") {
		std::cout << " hit brick ";
		//rbody->currentVelocity.y *= -1.0f;
	}
}
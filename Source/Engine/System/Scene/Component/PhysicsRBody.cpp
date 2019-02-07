#include "PhysicsRBody.h"
#include "../../Physics/PhysicsSystem.h"
#include "../GameObject.h"
#include "../Component/TransformComponent.h"
#include "../Component/SpriteRenderer.h"
#include <cstdlib>

PhysicsRBody::PhysicsRBody() {
}

void PhysicsRBody::Init() {
	SetAABB();
	engine = PhysicsSystem::GetInstance();
	engine->AddRigidBody(this);
	gravity.x = PhysicsSystem::DEFAULT_GRAVITY.x;
	gravity.y = PhysicsSystem::DEFAULT_GRAVITY.y;
}

PhysicsRBody::~PhysicsRBody() {
}

void PhysicsRBody::AddForce(sf::Vector2f force) {
	totalForces += force;
}

void PhysicsRBody::Stop() {
	currentVelocity.x = 0.0f;
	currentVelocity.y = 0.0f;

	totalForces.x = 0.0f;
	totalForces.y = 0.0f;
}

bool PhysicsRBody::IsGrounded() {
	grounded = engine->IsGrounded(this);
	return grounded;
}

void PhysicsRBody::Integrate(float dT) {
	sf::Vector2f acceleration;

	if (obeysGravity && !IsGrounded()) {
		acceleration = gravity;
	}
	else {
		if (std::abs(currentVelocity.y) < 0.05f) {
			currentVelocity.y = 0.0f;
		}
	}

	if (mass == 0.0f) {
		acceleration.x = 0.0f;
		acceleration.y = 0.0f;
	}
	else {
		acceleration += totalForces / mass;
	}

	currentVelocity += acceleration * dT;
	gameObject->GetTransform().translate(currentVelocity * dT);
	SetAABB();
	totalForces.x = 0.f;
	totalForces.y = 0.f;
}

ComponentType PhysicsRBody::GetComponentType() {
	return C_PhysicsRBody;
}

void PhysicsRBody::SetAABB() {
	BaseComponent* r = gameObject->GetComponent(C_SpriteRenderer);
	if (r) {
		SpriteRenderer* sr = (SpriteRenderer*)r;
		sf::FloatRect rect = gameObject->GetWorldTransform().transformRect(sr->sprite.getGlobalBounds());

		aabb.bLeft.x = rect.left;
		aabb.bLeft.y = -rect.top - rect.height;

		aabb.tRight.x = rect.left + rect.width;
		aabb.tRight.y = -rect.top;

		canCollide = true;
	}else {
		canCollide = false;
	}
}
#include "TransformComponent.h"
#include "../GameObject.h"

using namespace sf;

TransformComponent::TransformComponent() {
	translation.x = 0.f;
	translation.y = 0.f;
	rotation = 0.f;
	scale.x = 0.f;
	scale.y = 0.f;
}

void TransformComponent::SetTransform(Transform& matrix) {
	transform = matrix;
}

Transform& TransformComponent::GetTransform() {
	return transform;
}

Transform& TransformComponent::GetWorldTransform() {
	return worldTransform;
}

void TransformComponent::Translate(sf::Vector2f t) {
	translation += t;
}

void TransformComponent::Rotate(float r) {
	rotation += r;
}

void TransformComponent::Scale(sf::Vector2f s) {
	scale += s;
}

Vector2f TransformComponent::GetPosition() {
	return translation;
}

void TransformComponent::Update(float msec) {
	transform = sf::Transform::Identity;
	transform.translate(translation).rotate(rotation).scale(scale);

	GameObject* p = gameObject->GetParent();
	if (p) {
		TransformComponent* t = p->Transform();
		worldTransform = t->GetWorldTransform() * transform;
	}
	else {
		worldTransform = transform;
	}
}

ComponentType TransformComponent::GetComponentType() {
	return C_Transform;
}
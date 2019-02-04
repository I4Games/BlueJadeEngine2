#include "TransformComponent.h"
#include "../GameObject.h"

using namespace sf;


void TransformComponent::SetTransform(Transform& matrix) {
	transform = matrix;
}

Transform& TransformComponent::GetTransform() {
	return transform;
}

Transform& TransformComponent::GetWorldTransform() {
	return worldTransform;
}

void TransformComponent::Update(float msec) {
	GameObject* p = gameObject->GetParent();
	if (p) {
		TransformComponent* t = p->GetTransformComponent();
		worldTransform = t->GetWorldTransform() * transform;
	}
	else {
		worldTransform = transform;
	}
}

ComponentType TransformComponent::GetComponentType() {
	return C_Transform;
}
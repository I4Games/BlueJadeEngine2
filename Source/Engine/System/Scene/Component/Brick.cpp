#include "Brick.h"
#include "../GameObject.h"
#include "../../Input/InputManager.h"
#include "../GameObjectManager.h"
#include <SFML/Graphics.hpp>

ComponentType Brick::GetComponentType() {
	return C_Brick;
}

void Brick::Init() {
	rbody = (PhysicsRBody*)(gameObject->GetComponent(C_PhysicsRBody));
}

void Brick::Update(float msec){
	
}

void Brick::OnCollisionDetected(GameObject* other, CollisionSide side) {
}
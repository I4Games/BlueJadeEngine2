#include "GameObject.h"
#include "Component\BaseComponent.h"
#include "Component\TransformComponent.h"

GameObject::GameObject(std::string& name) {
	parent = NULL;
	this->name = name;
	transform = new TransformComponent();
	AddComponent(transform);
}

GameObject::~GameObject(void) {
	for (unsigned int i = 0; i < children.size(); ++i) {
		delete children[i];
	}
	for (unsigned int i = 0; i < components.size(); ++i) {
		delete components[i];
	}
}

Transform& GameObject::GetTransform() {
	return transform->GetTransform();
}

Transform& GameObject::GetWorldTransform() {
	return transform->GetWorldTransform();
}

TransformComponent* GameObject::Transform() {
	return transform;
}

std::string GameObject::GetName() {
	return name;
}

std::string GameObject::GetTag() {
	return tag;
}

GameObject* GameObject::GetParent() {
	return parent;
}

void GameObject::SetParent(GameObject* p){
	parent = p;
}

void GameObject::AddChild(GameObject* s) {
	children.push_back(s);
	s->parent = this;
}

void GameObject::AddComponent(BaseComponent* c) {
	components.push_back(c);
	c->SetGameObject(this);
	c->Init();
}

void GameObject::SetTag(std::string newTag) {
	tag = newTag;
}

void GameObject::Translate(sf::Vector2f t) {
	transform->Translate(t);
}

void GameObject::Rotate(float r) {
	transform->Rotate(r);
}

void GameObject::Scale(sf::Vector2f s) {
	transform->Scale(s);
}

GameObject* GameObject::FindChildByName(std::string &name) {
	for (int i = 0; i < children.size(); ++i) {
		if (children[i]->GetName() == name) {
			return children[i];
		}else {
			GameObject* search = children[i]->FindChildByName(name);
			if (search) {
				return search;
			}
		}
	}

	return NULL;
}

void GameObject::RemoveChildren() {
	for (auto it = children.begin(); it != children.end(); ++it) {
		delete (*it);
	}
	children.clear();
}

BaseComponent* GameObject::GetComponent(ComponentType cType) {
	for (std::vector<BaseComponent*>::iterator i = components.begin(); i != components.end(); ++i) {
		if (cType == (*i)->GetComponentType()) {
			return (*i);
		}
	}

	return NULL;
}

void GameObject::Update(float msec) {
	for (std::vector<BaseComponent*>::iterator i = components.begin(); i != components.end(); ++i) {
		(*i)->Update(msec);
	}

	for (std::vector<GameObject*>::iterator i = children.begin(); i != children.end(); ++i) {
		(*i)->Update(msec);
	}
}

void GameObject::OnCollisionDetected(GameObject* other, CollisionSide side) {
	for (auto i = components.begin(); i != components.end(); ++i) {
		(*i)->OnCollisionDetected(other, side);
	}
}
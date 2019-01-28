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

TransformComponent* GameObject::GetTransform() {
	return transform;
}

std::string GameObject::GetName() {
	return name;
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

void GameObject::Update(float msec) {
	for (std::vector<BaseComponent*>::iterator i = components.begin(); i != components.end(); ++i) {
		(*i)->Update(msec);
	}

	for (std::vector<GameObject*>::iterator i = children.begin(); i != children.end(); ++i) {
		(*i)->Update(msec);
	}
}
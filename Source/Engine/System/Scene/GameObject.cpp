#include "GameObject.h"

GameObject::~GameObject(void) {
	for (unsigned int i = 0; i < children.size(); ++i) {
		delete children[i];
	}
}

void GameObject::AddChild(GameObject* s) {
	children.push_back(s);
	s->parent = this;
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
	if (parent) {
		worldTransform = parent->worldTransform * transform;
	}else {
		worldTransform = transform;
	}

	for (std::vector<GameObject*>::iterator i = children.begin(); i != children.end(); ++i) {
		(*i)->Update(msec);
	}
}
#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

using namespace sf;

class GameObject {
public:
	GameObject(std::string &name) { parent = NULL; this->name = name; }
	~GameObject(void);

	void SetTransform(const Transform &matrix) { transform = matrix; }
	Transform GetTransform() { return transform; }
	Transform GetWorldTransform() { return worldTransform; }
	std::string GetName() { return name; }

	void SetParent(GameObject* p) { parent = p; }
	void AddChild(GameObject* s);
	GameObject* FindChildByName(std::string &name);

	virtual void Update(float msec);

protected:
	GameObject* parent;
	std::string name;
	Transform worldTransform;
	Transform transform;
	std::vector<GameObject*> children;
};
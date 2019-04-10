#ifndef BLUEJADE_TRANSFORMCOMPONENT
#define BLUEJADE_TRANSFORMCOMPONENT

#include "BaseComponent.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class TransformComponent : public BaseComponent {
public:
	TransformComponent();

	void SetTransform(Transform &matrix);
	Transform& GetTransform();
	Transform& GetWorldTransform();
	void Translate(sf::Vector2f t);
	void Rotate(float r);
	void Scale(sf::Vector2f s);
	Vector2f GetPosition();

	//Base Component
	virtual void Update(float msec);
	virtual void Init() {};
	virtual ComponentType GetComponentType();

protected:
	Transform transform;
	Transform worldTransform;
	Vector2f translation;
	float rotation;
	Vector2f scale;
};

#endif
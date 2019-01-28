#ifndef BLUEJADE_TRANSFORMCOMPONENT
#define BLUEJADE_TRANSFORMCOMPONENT

#include "BaseComponent.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class TransformComponent : public BaseComponent {
public:
	void SetTransform(Transform &matrix);
	Transform GetTransform();
	Transform GetWorldTransform();

	virtual void Update(float msec);

protected:
	Transform transform;
	Transform worldTransform;
};

#endif
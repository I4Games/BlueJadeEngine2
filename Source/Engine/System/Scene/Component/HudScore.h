#pragma once
#include "BaseComponent.h"
#include "TextRenderer.h"

#include "PhysicsRBody.h"

class HudScore : public BaseComponent {
public:
	TextRenderer* label;

	//Base Component
	virtual ComponentType GetComponentType();
	virtual void Init();
	virtual void Update(float msec);
};
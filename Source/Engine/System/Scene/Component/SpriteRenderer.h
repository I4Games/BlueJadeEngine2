#pragma once
#include "BaseComponent.h"
#include <SFML/Graphics.hpp>

class SpriteRenderer : public BaseComponent {
public:
	//Members
	sf::Sprite sprite;

	//Methods
	void SetSpriteFromFile(std::string filename);

	//BaseComponent
	virtual void Update(float msec);
	virtual ComponentType GetComponentType();
};
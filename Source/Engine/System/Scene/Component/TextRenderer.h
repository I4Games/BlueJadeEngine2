#pragma once
#include "BaseComponent.h"
#include <SFML/Graphics.hpp>

class TextRenderer : public BaseComponent {
public:
	//Members
	sf::Text text;

	//Methods
	void SetFont(std::string filename);

	void SetText(std::string text);
	void SetSize(int textSize);
	void SetColor(sf::Color color);

	//BaseComponent
	virtual void Update(float msec);
	virtual void Init() {}
	virtual ComponentType GetComponentType();
};
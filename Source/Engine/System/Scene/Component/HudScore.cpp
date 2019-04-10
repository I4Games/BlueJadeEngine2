#include "HudScore.h"
#include "../GameObject.h"
#include "../../Input/InputManager.h"
#include <SFML/Graphics.hpp>

ComponentType HudScore::GetComponentType() {
	return C_Score;
}

void HudScore::Init() {
	label = (TextRenderer*)(gameObject->GetComponent(C_TextRenderer));
}

void HudScore::Update(float msec) {

	std::cout << " HudScore ";

	//label->SetFont("../Assets/Fonts/Sansation.ttf");
	//label->SetText("[SCORE]");
	label->SetColor(sf::Color(180, 180, 180));
	label->SetSize(30);
}
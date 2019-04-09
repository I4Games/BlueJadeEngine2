#include "TextRenderer.h"
#include "../GameObject.h"
#include "../../Graphics/GraphicsSystem.h"


void TextRenderer::SetFont(std::string filename){
	sf::Font font;
	text.setFont(font);
	if (!font.loadFromFile(filename))
	{
		return;
	}
}

void TextRenderer::SetText(std::string t){
	text.setString(t);
}

void TextRenderer::SetSize(int textSize){
	text.setCharacterSize(textSize);
}

void TextRenderer::SetColor(sf::Color color){
	text.setFillColor(color);
}

void TextRenderer::Update(float msec){
	GraphicsSystem::GetInstance()->AddDrawable(&text, &(gameObject->GetWorldTransform()));
	//GraphicsSystem::GetInstance()->AddText(text, &(gameObject->GetTransform().translate));
	//GraphicsSystem::GetInstance()->AddText(&text);
}

ComponentType TextRenderer::GetComponentType(){
	return C_TextRenderer;
}

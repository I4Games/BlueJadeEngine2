#include "TextRenderer.h"
#include "../GameObject.h"
#include "../../Graphics/GraphicsSystem.h"

TextRenderer::~TextRenderer(){
	GraphicsSystem::GetInstance()->RemoveDrawable(&text, &(gameObject->GetWorldTransform()));
}

void TextRenderer::SetFont(std::string filename){
	if (!font.loadFromFile(filename))
	{
		return;
	}
	text.setFont(font);
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
}

ComponentType TextRenderer::GetComponentType(){
	return C_TextRenderer;
}

#include "SpriteRenderer.h"
#include "../GameObject.h"
#include "../../Graphics/GraphicsSystem.h"

void SpriteRenderer::SetSpriteFromFile(std::string filename) {
	sf::Image image;
	if (!image.loadFromFile(filename)) {
		return;
	}

	texture.loadFromImage(image);
	sprite.setTexture(texture);
}

void SpriteRenderer::Update(float msec) {
	GraphicsSystem::GetInstance()->AddDrawable(&sprite, &(gameObject->GetWorldTransform()));
}

ComponentType SpriteRenderer::GetComponentType() {
	return C_SpriteRenderer;
}
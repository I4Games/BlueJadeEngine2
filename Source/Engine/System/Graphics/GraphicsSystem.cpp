#include "GraphicsSystem.h"

GraphicsSystem* GraphicsSystem::Instance = 0;

GraphicsSystem* GraphicsSystem::GetInstance() {
	if (!Instance) {
		Instance = new GraphicsSystem();
	}
	return Instance;
}

GraphicsSystem::GraphicsSystem() {
	window.create(sf::VideoMode(InitialWindowWidth, InitialWindowHeight), WindowTitle);
}

void GraphicsSystem::ShowSplash() {
	sf::Image BJ2Logo;
	if (!BJ2Logo.loadFromFile("../Assets/BJ2Logo.png"))
		return;

	sf::Texture logoTexture;
	logoTexture.loadFromImage(BJ2Logo);
	sf::Sprite logoSprite;
	logoSprite.setTexture(logoTexture);

	sf::Vector2f windowSize = window.getView().getSize();

	logoSprite.setScale(
		windowSize.x / logoSprite.getLocalBounds().width,
		windowSize.y / logoSprite.getLocalBounds().height
	);
	window.draw(logoSprite);
	window.display();
}

void GraphicsSystem::OnCloseApp() {
	window.clear();
	window.close();
}

void GraphicsSystem::Render() {
	window.clear();
	for (std::vector<DrawSpec>::iterator i = drawables.begin(); i != drawables.end(); ++i) {
		window.draw(*((*i).drawable), *((*i).transform));
	}
	window.display();
	drawables.clear();
}

void GraphicsSystem::AddDrawable(sf::Drawable* d, sf::Transform* t) {
	DrawSpec s;
	s.drawable = d;
	s.transform = t;
	drawables.push_back(s);
}
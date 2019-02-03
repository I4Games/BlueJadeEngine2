#pragma once
#include <SFML/Graphics.hpp>

class GraphicsSystem {
public:
	//Members
	int InitialWindowWidth = 1000;
	int InitialWindowHeight = 700;
	std::string WindowTitle = "BlueJade-II";

	//Methods
	GraphicsSystem();

	sf::RenderWindow& GetWindow() { return window; }
	void ShowSplash();
	void OnCloseApp();

private:
	sf::RenderWindow window;
};
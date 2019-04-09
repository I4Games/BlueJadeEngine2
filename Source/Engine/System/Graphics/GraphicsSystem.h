#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct DrawSpec {
	sf::Drawable* drawable;
	sf::Transform* transform;
};

class GraphicsSystem {
public:
	//Members
	static GraphicsSystem* GetInstance();

	int InitialWindowWidth = 1000;
	int InitialWindowHeight = 700;
	std::string WindowTitle = "BlueJade-II";

	//Methods
	GraphicsSystem();

	sf::RenderWindow& GetWindow() { return window; }
	void ShowSplash();
	void OnCloseApp();
	void Render();

	void AddDrawable(sf::Drawable* d, sf::Transform* t);
	void AddShape(sf::Shape* shape);
	//void AddText(sf::Text text, sf::Vector2f* v);
	//void AddText(sf::Text* text);

private:
	static GraphicsSystem* Instance;

	//Members
	sf::RenderWindow window;
	std::vector<DrawSpec> drawables;
	std::vector<sf::Shape*> shapes;
	std::vector<sf::Text*> texts;
};
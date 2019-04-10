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

	int WindowWidth = 1000;
	int WindowHeight = 700;
	std::string WindowTitle = "BlueJade-II";

	//Methods
	GraphicsSystem();

	sf::RenderWindow& GetWindow() { return window; }
	void ShowSplash();
	void OnCloseApp();
	void Render();

	void AddDrawable(sf::Drawable* d, sf::Transform* t);
	void RemoveDrawable(sf::Drawable* d, sf::Transform* t);
	void AddShape(sf::Shape* shape);

private:
	static GraphicsSystem* Instance;

	//Members
	sf::RenderWindow window;
	std::vector<DrawSpec> drawables;
	std::vector<sf::Shape*> shapes;
	std::vector<sf::Text*> texts;
};
//mouse input: 
//https://docs.microsoft.com/en-us/windows/desktop/inputdev/using-mouse-input
//keyboard input:
//https://docs.microsoft.com/en-us/windows/desktop/inputdev/using-keyboard-input

#include "BlueJadeII.h"

BlueJadeII::BlueJadeII()
{
	this->InitializeWindow();
}

void BlueJadeII::InitializeWindow() 
{
	window.create(VideoMode(WindowWidth, WindowHeight), WindowTitle);
}

void BlueJadeII::Render()
{
	CircleShape shape(100.f);
	shape.setFillColor(Color::Green);

	window.clear();
	window.draw(shape);
	window.display();
}

void BlueJadeII::Update()
{
	
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		
		Render();

	}
}

void BlueJadeII::Start() 
{
	Update();
}

void BlueJadeII::CloseApp()
{
	window.clear();
	window.close();
}
#pragma once
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <tchar.h>
#include <direct.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include <iostream>

using namespace std;
using namespace sf;

class BlueJadeII {
public:
	//Members

	int WindowWidth = 500;
	int WindowHeight = 500;
	string WindowTitle = "BlueJade-II";

	BlueJadeII();

	//Methods

	void Start();
	void CloseApp();

private:
	/****
	Members
	****/
	RenderWindow window;

	/****
	Methods
	****/

	//Create a new window
	void InitializeWindow();

	//Called to draw stuff
	void Render();

	//Called every frame
	void Update();

};
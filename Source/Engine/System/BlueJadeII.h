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
#include "Scene\GameObjectManager.h"
#include "Scene\GameObject.h"
#include "Graphics\GraphicsSystem.h"

#define DEFAULT_STORAGE_NEEDED 314572800
#define MAX_CONTIGUOUS_MEMORY_NEEDED 314572800
#define MB_CONVERSION 1048576
#define GB_CONVERSION 1073741824

using namespace std;
using namespace sf;

class BlueJadeII {
public:
	//Members

	int WindowWidth = 1000;
	int WindowHeight = 700;
	string WindowTitle = "BlueJade-II";

	BlueJadeII();

	//Methods

	void Start();
	void CloseApp();
	bool InitializeEngine();
	void InitializeSystems();

	//**
	//GameObject
	//**

	GameObject* AddGameObject(string name);
	BaseComponent* MakeComponent(ComponentType cType);

protected:
	/****
	Members
	****/
	GameObjectManager* gameObjectManager;

	Clock clock;
	HANDLE m_MutexHandle;

	enum GameState {Uninitialized, Initializing, ShowingSplash, Paused, Playing, Exiting};
	GameState gameState;

	/****
	Methods
	****/

	//**
	//Initialization
	//**

	//Check if there is another instance of the engine running
	bool IsOnlyInstance();

	//Check if the platform has enough storage
	bool CheckStorage();

	//Display Memory Information
	void DisplayMemoryInfo();

	//Get CPU Architecture
	string GetCPUArchitecture();

	//Get CPU Speed
	int GetCPUSpeed();

	//Create a new window
	void InitializeWindow();

	//**
	//Graphics
	//**

	//Display the splash screen
	void Splash();

	//Called to draw stuff
	void Render();

	//**
	//GameObject
	//**

	//**
	//Lifecycle
	//**

	//Called every frame
	void Update();

};
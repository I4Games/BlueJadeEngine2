#include <SFML/Graphics.hpp>

#include "BlueJadeII.h"

#include "Physics\PhysicsSystem.h"

#include "Scene\Component\BaseComponent.h"
#include "Scene\SceneManager.h"

#include "Event\EventManager.h"

#include "Input\InputManager.h"

BlueJadeII::BlueJadeII()
{
	gameState = Uninitialized;
}

bool BlueJadeII::InitializeEngine() 
{
	if (!IsOnlyInstance()) {
		cout << "Another instance of the game is running. Exiting..." << endl;
		return false;
	}else {
		cout << "No other instance of the game is running" << endl;
	}

	if (!CheckStorage()) {
		cout << "Not enough space on disk. Exiting..." << endl;
		return false;
	}else {
		cout << "Disk has enough space" << endl;
	}

	DisplayMemoryInfo();

	cout << "CPU Architecture: " << GetCPUArchitecture() << endl;
	cout << "CPU Speed: " << GetCPUSpeed() << " MHz" << endl;

	this->InitializeWindow();
	this->Splash();

	if (gameState == Exiting) {
		return false;
	}

	this->InitializeSystems();

	return true;
}

void BlueJadeII::InitializeSystems() {
	gameState = Playing;
}

GameObject* BlueJadeII::AddGameObject(string name) {
	GameObject* obj = new GameObject(name);
	GameObjectManager::GetInstance()->AddGameObject(obj, NULL);

	return obj;
}

BaseComponent* BlueJadeII::MakeComponent(ComponentType cType) {
	return SceneManager::MakeComponent(cType);
}

GameObject* BlueJadeII::FindGameObject(string name) {
	return GameObjectManager::GetInstance()->GetGameObjectByName(name);
}

void BlueJadeII::AddEventListener(const EventType& t, void(*foo)(IEventData*)) {
	EventManager::GetInstance()->VAddListener(EventListenerDelegate(foo), t);
}

void BlueJadeII::OpenScene(std::string filename) {
	SceneManager::GetInstance()->BuildScene(filename);
}

void BlueJadeII::Splash()
{
	Clock clock;
	Time timeToClose = seconds(2.f);

	GraphicsSystem* g = GraphicsSystem::GetInstance();

	RenderWindow& window = g->GetWindow();
	g->ShowSplash();

	//Set up events/conditions for the splash screen to transition into the app later
	Event e;
	while (gameState == ShowingSplash) {
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::EventType::Closed) {
				gameState = Exiting;
				return;
			}
		}
		timeToClose -= clock.restart();
		if (timeToClose.asSeconds() <= 0) {
			gameState = Initializing;
			return;
		}
	}

}

void BlueJadeII::InitializeWindow()
{
	gameState = ShowingSplash;
}

bool BlueJadeII::IsOnlyInstance() 
{
	m_MutexHandle = CreateMutex(NULL, TRUE, WindowTitle.c_str());

	if (GetLastError() != ERROR_SUCCESS) {
		HWND hWnd = FindWindow(WindowTitle.c_str(), NULL);
		if (hWnd) {
			ShowWindow(hWnd, SW_SHOWNORMAL);
			SetFocus(hWnd);
			SetForegroundWindow(hWnd);
			SetActiveWindow(hWnd);
		}
		return false;
	}

	return true;
}

bool BlueJadeII::CheckStorage() 
{
	//Get the address of the current drive
	int const drive = _getdrive();

	//Initialize a structure containing information about the current disk
	struct _diskfree_t diskfree;
	_getdiskfree(drive, &diskfree);

	//Calculate the amount of clusters needed in memory
	unsigned __int64 neededClusters;
	neededClusters = DEFAULT_STORAGE_NEEDED /
		(diskfree.sectors_per_cluster * diskfree.bytes_per_sector);

	//Determine if we have enough clusters
	if (diskfree.avail_clusters < neededClusters) {
		cout << "CheckStorage Failure: Not enough physical storage" << endl;
		return false;
	}

	return true;
}

void BlueJadeII::DisplayMemoryInfo() {
	//Get the global memory status
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);

	//Display total RAM available
	DWORDLONG tempV = status.ullAvailPhys / GB_CONVERSION;
	string msgRAM;
	msgRAM += "Total RAM: ";
	msgRAM += std::to_string(tempV);
	msgRAM += " GB available";
	cout << msgRAM << endl;


	//Display total VRAM available
	DWORDLONG tempvalue = status.ullAvailVirtual / GB_CONVERSION;
	string outmsg;
	outmsg += "Total VRAM: ";
	outmsg += std::to_string(tempvalue);
	outmsg += " GB available \n";
	cout << outmsg << endl;


	//Determine contiguousness of memory (based on the max amount of VRAM the engine would use)
	char *buff = new char[MAX_CONTIGUOUS_MEMORY_NEEDED];
	if (buff) {
		delete[] buff;
		cout << "The system has " << MAX_CONTIGUOUS_MEMORY_NEEDED / MB_CONVERSION << " MB of memory in a single block available" << endl;
	}
	else {
		cout << "The system does not have " << MAX_CONTIGUOUS_MEMORY_NEEDED / MB_CONVERSION << " MB of memory in a single block available" << endl;
	}
}

string BlueJadeII::GetCPUArchitecture() {
	//Get system information
	SYSTEM_INFO system_info;
	GetNativeSystemInfo(&system_info);

	//Retrieve the architecure ID
	WORD arch_id = system_info.wProcessorArchitecture;

	//Return a value depending on the architecture ID
	switch (arch_id) {
	case PROCESSOR_ARCHITECTURE_AMD64:
		return "x64";
	case PROCESSOR_ARCHITECTURE_ARM:
		return "ARM";
	case PROCESSOR_ARCHITECTURE_ARM64:
		return "ARM64";
	case PROCESSOR_ARCHITECTURE_IA64:
		return "Intel Itanium-based";
	case PROCESSOR_ARCHITECTURE_INTEL:
		return "x86";
	case PROCESSOR_ARCHITECTURE_UNKNOWN:
		return "Unknown architecture";
	default:
		return "Invalid or unrecognized architecture code";
	}
}

int BlueJadeII::GetCPUSpeed() {
	DWORD BufSize = sizeof(DWORD);
	DWORD dwMHz = 0;
	DWORD type = REG_DWORD;
	HKEY hKey;

	//Check the registry for the key that holds cpu speed
	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
		0,
		KEY_READ,
		&hKey);

	//If the key was foundm query it for the value we need
	if (lError == ERROR_SUCCESS) {
		RegQueryValueEx(hKey, "~MHz", NULL, NULL, (LPBYTE)&dwMHz, &BufSize);
	}

	return dwMHz;
}


void BlueJadeII::Render()
{
	GraphicsSystem::GetInstance()->Render();
}

void BlueJadeII::Update()
{
	RenderWindow& window = GraphicsSystem::GetInstance()->GetWindow();

	while (gameState != Exiting)
	{
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
				case Event::Closed:
					window.close();
					gameState = Exiting;
					break;
				case Event::KeyPressed:
					InputManager::GetInstance()->KeyDown(event.key.code);
					break;
				case Event::KeyReleased:
					InputManager::GetInstance()->KeyUp(event.key.code);
					break;
			}
		}

		Time elapsed = clock.restart();

		EventManager::GetInstance()->VUpdate();
		SceneManager::GetInstance()->Update();
		GameObjectManager::GetInstance()->Update(elapsed.asSeconds());
		InputManager::GetInstance()->Update();
		PhysicsSystem::GetInstance()->Update(elapsed.asSeconds());

		Render();
	}
}

void BlueJadeII::luaTest()
{
	/* initialize Lua */
	L = luaL_newstate();

	/* load Lua base libraries */
	luaL_openlibs(L);

	/* run the script */
	luaL_dofile(L, "../Source/LuaFunc/test.lua");

	/* cleanup Lua */
	lua_close(L);
}

void BlueJadeII::Start() 
{
	luaTest();
	clock.restart();
	Update();
}

void BlueJadeII::CloseApp()
{
	GraphicsSystem::GetInstance()->OnCloseApp();
}
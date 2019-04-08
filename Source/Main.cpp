#include "Engine/System/BlueJadeII.h"
#include "Engine/System/Scene/Component/SpriteRenderer.h"
#include "Engine/System/Scene/Component/PhysicsRBody.h"
#include "Engine/System/Scene/Component/TransformComponent.h"
#include "Engine/System/Scene/Component/AudioPlayer.h"
#include "Engine/System/Event/EventData/EvtData_Keydown.h"

#include <SFML/Graphics.hpp>

#include <windows.h>  
#include <stdlib.h>  
#include <string.h>  
#include <tchar.h>	



BlueJadeII* mGameApp = nullptr;

int main(){
	
	mGameApp = new BlueJadeII();

	if (!mGameApp->InitializeEngine()) {
		cout << "Failed to initialize the instance" << endl;
		return 1;
	}

	mGameApp->OpenScene("../Assets/Scenes/Level_1.xml");
	
	mGameApp->Start();

	return 0;
}
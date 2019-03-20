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
GameObject* ballChild;
GameObject* ball;

void BallMoveDelegate(IEventData* p) {
	float mov = 2.f;
	EvtData_Keydown* pEvent = (EvtData_Keydown*)p;
	switch (pEvent->GetKeyCode()) {
		case sf::Keyboard::Left:
			ballChild->Translate(sf::Vector2f(-mov, 0.f));
			break;
		case sf::Keyboard::Right:
			ballChild->Translate(sf::Vector2f(mov, 0.f));
			break;
		case sf::Keyboard::Up:
			ballChild->Translate(sf::Vector2f(0.f, -mov));
			break;
		case sf::Keyboard::Down:
			ballChild->Translate(sf::Vector2f(0.f, mov));
			break;
	}
}

void BigBallMoveDelegate(IEventData* p) {
	float mov = 2.f;
	EvtData_Keydown* pEvent = (EvtData_Keydown*)p;
	switch (pEvent->GetKeyCode()) {
	case sf::Keyboard::A:
		ball->Translate(sf::Vector2f(-mov, 0.f));
		break;
	case sf::Keyboard::D:
		ball->Translate(sf::Vector2f(mov, 0.f));
		break;
	case sf::Keyboard::W:
		ball->Translate(sf::Vector2f(0.f, -mov));
		break;
	case sf::Keyboard::S:
		ball->Translate(sf::Vector2f(0.f, mov));
		break;
	}
}

int main(){
	
	mGameApp = new BlueJadeII();

	if (!mGameApp->InitializeEngine()) {
		cout << "Failed to initialize the instance" << endl;
		return 1;
	}

	mGameApp->OpenScene("../Assets/Scenes/SampleScene.xml");
	
	ball = mGameApp->FindGameObject("Ball");
	ballChild = mGameApp->FindGameObject("BallChild");

	EvtData_Keydown* pt = new EvtData_Keydown(2);
	mGameApp->AddEventListener(pt->VGetEventType(), &BallMoveDelegate);
	mGameApp->AddEventListener(pt->VGetEventType(), &BigBallMoveDelegate);
	
	mGameApp->Start();

	return 0;
}
#include "Engine/System/BlueJadeII.h"
#include "Engine/System/Scene/Component/SpriteRenderer.h"
#include "Engine/System/Scene/Component/PhysicsRBody.h"
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
			ballChild->GetTransform().translate(-mov, 0.f);
			break;
		case sf::Keyboard::Right:
			ballChild->GetTransform().translate(mov, 0.f);
			break;
		case sf::Keyboard::Up:
			ballChild->GetTransform().translate(0.f, -mov);
			break;
		case sf::Keyboard::Down:
			ballChild->GetTransform().translate(0.f, mov);
			break;
	}
}

void BigBallMoveDelegate(IEventData* p) {
	float mov = 2.f;
	EvtData_Keydown* pEvent = (EvtData_Keydown*)p;
	switch (pEvent->GetKeyCode()) {
	case sf::Keyboard::A:
		ball->GetTransform().translate(-mov, 0.f);
		break;
	case sf::Keyboard::D:
		ball->GetTransform().translate(mov, 0.f);
		break;
	case sf::Keyboard::W:
		ball->GetTransform().translate(0.f, -mov);
		break;
	case sf::Keyboard::S:
		ball->GetTransform().translate(0.f, mov);
		break;
	}
}

int main(){
	
	mGameApp = new BlueJadeII();

	if (!mGameApp->InitializeEngine()) {
		cout << "Failed to initialize the instance" << endl;
		return 1;
	}

	//Ball
	
	ball = mGameApp->AddGameObject("Ball");
	
	SpriteRenderer* ballRenderer = (SpriteRenderer*) mGameApp->MakeComponent(C_SpriteRenderer);
	ballRenderer->SetSpriteFromFile("../Assets/puzzlepack/png/ballBlue.png");

	PhysicsRBody* ballRBody = (PhysicsRBody*)mGameApp->MakeComponent(C_PhysicsRBody);
	ballRBody->bounciness = 0.6f;

	AudioPlayer* ballPlayer = (AudioPlayer*)mGameApp->MakeComponent(C_AudioPlayer);
	ballPlayer->playBGM("../Assets/sound/doctor.ogg");
	
	ball->AddComponent(ballRenderer);
	ball->GetTransform().translate(250.f, 120.f).scale(2.0f,2.0f);

	ball->AddComponent(ballRBody);

	ball->AddComponent(ballPlayer);

	//Ball Child

	ballChild = mGameApp->AddGameObject("BallChild");

	SpriteRenderer* ballChildRenderer = (SpriteRenderer*)mGameApp->MakeComponent(C_SpriteRenderer);
	ballChildRenderer->SetSpriteFromFile("../Assets/puzzlepack/png/ballGrey.png");

	ballChild->AddComponent(ballChildRenderer);
	ballChild->GetTransform().translate(180.f, 0.f).scale(0.5f, 0.5f);

	ball->AddChild(ballChild);

	//Platform

	GameObject* platform = mGameApp->AddGameObject("Platform");
	
	SpriteRenderer* platformRenderer = (SpriteRenderer*) mGameApp->MakeComponent(C_SpriteRenderer);
	platformRenderer->SetSpriteFromFile("../Assets/puzzlepack/png/buttonDefault.png");

	PhysicsRBody* platformRBody = (PhysicsRBody*)mGameApp->MakeComponent(C_PhysicsRBody);
	platformRBody->obeysGravity = false;
	platformRBody->mass = 0.f;

	platform->AddComponent(platformRenderer);
	platform->GetTransform().translate(250.0f, 300.f);

	platform->AddComponent(platformRBody);

	EvtData_Keydown* pt = new EvtData_Keydown(2);
	mGameApp->AddEventListener(pt->VGetEventType(), &BallMoveDelegate);
	mGameApp->AddEventListener(pt->VGetEventType(), &BigBallMoveDelegate);
	
	mGameApp->Start();

	return 0;
}
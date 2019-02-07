#include "Engine/System/BlueJadeII.h"
#include "Engine/System/Scene/Component/SpriteRenderer.h"
#include "Engine/System/Scene/Component/PhysicsRBody.h"

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

	//Ball
	
	GameObject* ball = mGameApp->AddGameObject("Ball");
	
	SpriteRenderer* ballRenderer = (SpriteRenderer*) mGameApp->MakeComponent(C_SpriteRenderer);
	ballRenderer->SetSpriteFromFile("../Assets/puzzlepack/png/ballBlue.png");

	PhysicsRBody* ballRBody = (PhysicsRBody*)mGameApp->MakeComponent(C_PhysicsRBody);
	ballRBody->bounciness = 0.6f;
	
	ball->AddComponent(ballRenderer);
	ball->GetTransform().translate(250.f, 120.f).scale(2.0f,2.0f);

	ball->AddComponent(ballRBody);

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
	
	mGameApp->Start();

	return 0;
}
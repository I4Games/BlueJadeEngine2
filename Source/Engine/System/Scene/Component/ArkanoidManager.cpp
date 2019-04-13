#include "ArkanoidManager.h"
#include "../GameObjectManager.h"
#include "../SceneManager.h"
#include "../../Input/InputManager.h"
#include <string>

ArkanoidManager* ArkanoidManager::Instance = 0;

ArkanoidManager* ArkanoidManager::GetInstance() {
	if (!Instance) {
		Instance = new ArkanoidManager();
	}
	return Instance;
}

ArkanoidManager::~ArkanoidManager() {
	if (Instance == this) {
		Instance = nullptr;
	}
}

ComponentType ArkanoidManager::GetComponentType() {
	return C_ArkanoidManager;
}

void ArkanoidManager::Init() {
	if (Instance != nullptr && Instance != this) {
		GameObjectManager::GetInstance()->DestroyGameObject(gameObject);
		return;
	}

	Instance = this;
	audioPlayer = (AudioPlayer*)gameObject->GetComponent(C_AudioPlayer);

	targetScore = GameObjectManager::GetInstance()->GetGameObjectsByName("Brick").size();

	GameObject* scoreObj = GameObjectManager::GetInstance()->GetGameObjectByName(scoreObjName);
	scoreText = (TextRenderer*)scoreObj->GetComponent(C_TextRenderer);

	GameObject* livesObj = GameObjectManager::GetInstance()->GetGameObjectByName(livesObjName);
	livesText = (TextRenderer*)livesObj->GetComponent(C_TextRenderer);
}

void ArkanoidManager::Update(float msec) {
	std::string scor = "Score: " + std::to_string(score);
	std::string liv = "Lives: " + std::to_string(lives);

	scoreText->SetText(scor);
	livesText->SetText(liv);

	if (InputManager::GetInstance()->IsKeyDown(sf::Keyboard::N)){
		OnWinLevel();
	}
}

void ArkanoidManager::SetLives(int s) {
	lives = s;
}

void ArkanoidManager::SetScore(int s) {
	score = s;
}

void ArkanoidManager::OnBrickDestroyed() {
	++score;
	audioPlayer->PlaySound();

	if (score == targetScore) {
		OnWinLevel();
	}
}

void ArkanoidManager::OnLifeLost() {
	--lives;
	if (lives == 0) {
		SceneManager::GetInstance()->RequestSceneChange(loseLevel);
	}
}

void ArkanoidManager::OnWinLevel() {
	SceneManager::GetInstance()->RequestSceneChange(winLevel);
}
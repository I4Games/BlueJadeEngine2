#include "ArkanoidManager.h"
#include "../GameObjectManager.h"
#include "../SceneManager.h"
#include <string>

ArkanoidManager* ArkanoidManager::Instance = 0;

ArkanoidManager* ArkanoidManager::GetInstance() {
	if (!Instance) {
		Instance = new ArkanoidManager();
	}
	return Instance;
}

ComponentType ArkanoidManager::GetComponentType() {
	return C_ArkanoidManager;
}

void ArkanoidManager::Init() {
	if (Instance != nullptr && Instance != this) {
		GameObjectManager::GetInstance()->DestroyGameObject(gameObject);
	}

	Instance = this;
	audioPlayer = (AudioPlayer*) gameObject->GetComponent(C_AudioPlayer);
}

void ArkanoidManager::Update(float msec) {
	std::string scor = "Score: " + std::to_string(score);
	std::string liv = "Lives: " + std::to_string(lives);

	scoreText->SetText(scor);
	livesText->SetText(liv);
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
}

void ArkanoidManager::OnLifeLost() {
	--lives;
	if (lives == 0) {
		SceneManager::GetInstance()->RequestSceneChange(loseLevel);
	}
}
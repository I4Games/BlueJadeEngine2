#pragma once
#include "BaseComponent.h"
#include "TextRenderer.h"
#include "AudioPlayer.h"

class ArkanoidManager : public BaseComponent {
public:
	static ArkanoidManager* GetInstance();

	~ArkanoidManager();

	//Base Component
	virtual ComponentType GetComponentType();
	virtual void Init();
	virtual void Update(float msec);

	//Members
	TextRenderer* scoreText;
	TextRenderer* livesText;
	std::string loseLevel;
	std::string winLevel;
	std::string scoreObjName;
	std::string livesObjName;

	//Methods
	void SetScore(int s);
	void SetLives(int s);
	void OnBrickDestroyed();
	void OnLifeLost();
	void OnWinLevel();

private:
	static ArkanoidManager* Instance;

	AudioPlayer* audioPlayer;
	int score;
	int lives;
	int targetScore;
};
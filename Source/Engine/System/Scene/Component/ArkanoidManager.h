#pragma once
#include "BaseComponent.h"
#include "TextRenderer.h"
#include "AudioPlayer.h"

class ArkanoidManager : public BaseComponent {
public:
	static ArkanoidManager* GetInstance();

	//Base Component
	virtual ComponentType GetComponentType();
	virtual void Init();
	virtual void Update(float msec);

	//Members
	TextRenderer* scoreText;
	TextRenderer* livesText;
	std::string loseLevel;

	//Methods
	void SetScore(int s);
	void SetLives(int s);
	void OnBrickDestroyed();
	void OnLifeLost();

private:
	static ArkanoidManager* Instance;

	AudioPlayer* audioPlayer;
	int score;
	int lives;
};
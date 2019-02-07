#pragma once
#include "BaseComponent.h"
#include <SFML\Audio.hpp>
#include <string>

class AudioPlayer : public BaseComponent {
public:
	sf::Music music;
	sf::Sound sound;
	sf::SoundBuffer buffer;

	void playBGM(std::string filename);
	void stopBGM();
	void LoadSound(std::string filename);
	void PlaySound();

	//Base Component
	virtual void Update(float msec) {}
	virtual void Init() {}
	virtual ComponentType GetComponentType();
};
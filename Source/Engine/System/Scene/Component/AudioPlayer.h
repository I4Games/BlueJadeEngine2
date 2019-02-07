#pragma once
#include "BaseComponent.h"
#include <SFML\Audio.hpp>
#include <string>

class AudioPlayer : public BaseComponent {
public:
	sf::Sound sound;
	sf::SoundBuffer buffer;

	void LoadSound(std::string filename);
	void PlaySound();

	//Base Component
	virtual void Update(float msec) {}
	virtual void Init() {}
	virtual ComponentType GetComponentType();
};
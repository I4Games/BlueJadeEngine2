#pragma once
#include <string>
#include <SFML/Audio.hpp>

class AudioSystem {
public:
	static AudioSystem* GetInstance();

	//Members
	sf::Music currentBGM;

	//Methods
	bool OpenBGM(std::string filename);
	void PlayBGM();
	void StopBGM();
	void LoadSound(sf::SoundBuffer& buffer, sf::Sound& sound, std::string filename);

private:
	static AudioSystem* Instance;
};
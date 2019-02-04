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
	sf::Sound& LoadSound(sf::SoundBuffer& buffer, std::string filename);

private:
	static AudioSystem* Instance;
};
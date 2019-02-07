#include "AudioSystem.h"

AudioSystem* AudioSystem::Instance = 0;

AudioSystem* AudioSystem::GetInstance() {
	if (!Instance) {
		Instance = new AudioSystem();
	}
	return Instance;
}

bool AudioSystem::OpenBGM(std::string filename) {
	return currentBGM.openFromFile(filename);
}

void AudioSystem::PlayBGM() {
	currentBGM.play();
}

void AudioSystem::StopBGM() {
	currentBGM.stop();
}

sf::Sound& AudioSystem::LoadSound(sf::SoundBuffer& buffer, std::string filename) {
	sf::Sound res;
	buffer.loadFromFile(filename);
	res.setBuffer(buffer);
	return res;
}
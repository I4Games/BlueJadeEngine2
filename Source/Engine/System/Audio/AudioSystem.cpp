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

void AudioSystem::LoadSound(sf::SoundBuffer& buffer, sf::Sound& sound, std::string filename) {
	buffer.loadFromFile(filename);
	sound.setBuffer(buffer);
}
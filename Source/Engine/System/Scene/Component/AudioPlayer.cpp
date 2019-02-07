#include "AudioPlayer.h"
#include "../../Audio/AudioSystem.h"
#include "../GameObject.h"

void AudioPlayer::LoadSound(std::string filename) {
	sound = AudioSystem::GetInstance()->LoadSound(buffer, filename);
}

void AudioPlayer::PlaySound() {
	sound.play();
}

ComponentType AudioPlayer::GetComponentType() {
	return C_AudioPlayer;
}
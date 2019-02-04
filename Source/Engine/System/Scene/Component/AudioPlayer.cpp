#include "AudioPlayer.h"
#include "../../Audio/AudioSystem.h"

void AudioPlayer::LoadSound(std::string filename) {
	sound = AudioSystem::GetInstance()->LoadSound(buffer, filename);
}

void AudioPlayer::PlaySound() {
	sound.play();
}
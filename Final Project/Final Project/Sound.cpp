#include "Sound.h"

Sound::Sound(int x, int y, float newLoudness, float newDuration, bool newNatural) {
	position = sf::Vector2f(x, y);
	loudness = newLoudness;
	duration = newDuration;
	natural = newNatural;
}

Sound::~Sound() { }

void Sound::update(float deltaTime) {
	duration -= deltaTime;
}

bool Sound::done() {
	return (duration < 0);
}
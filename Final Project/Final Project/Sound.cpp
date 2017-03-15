#include "Sound.h"

Sound::Sound(int x, int y, float newLoudness, float newDuration, bool newNatural) {
	position = sf::Vector2f(x, y);
	loudness = newLoudness;
	totalDuration = duration = newDuration;
	natural = newNatural;
}

Sound::~Sound() { }

void Sound::update(float deltaTime) {
	duration -= deltaTime;
}

sf::Vector2f& Sound::getPosition() { return position; }
float Sound::getLoudness() { return loudness; }
float Sound::getPercentTimeLeft() { return (1 - duration / totalDuration); }
bool Sound::isNatural() { return natural; }

bool Sound::done() {
	return (duration < 0);
}
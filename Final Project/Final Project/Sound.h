#pragma once
#include "Updatable.h"

class Sound : public Updatable {
public:
	Sound(int, int, float, float, bool);
	~Sound();

	void update(float);
	sf::Vector2f& getPosition();
	float getLoudness();
	bool isNatural();
	bool done();

private:
	float loudness;
	float duration;
	bool natural;
};
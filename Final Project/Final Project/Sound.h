#pragma once
#include "Updatable.h"

class Sound : public Updatable {
public:
	/*
	int: x coordinate, int: y coordinate, float: loadness, float: duration, bool: natural
	*/
	Sound(int, int, float, float, bool);
	~Sound();

	void update(float);
	sf::Vector2f& getPosition();
	float getLoudness();
	float getPercentTimeLeft();
	bool isNatural();
	bool done();

private:
	float loudness;
	float duration, totalDuration;
	bool natural;
};
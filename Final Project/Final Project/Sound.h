#pragma once
#include "Updatable.h"

class Sound : public Updatable {
public:
	Sound(int, int, float, float, bool);
	~Sound();

	void update(float);
	bool done();

	float loudness;
	float duration;
	bool natural;
};
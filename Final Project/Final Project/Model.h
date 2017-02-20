#pragma once

#include "Player.h"

class Model {
public:
	Model();
	~Model();

	void update(float);

	Player player;
};


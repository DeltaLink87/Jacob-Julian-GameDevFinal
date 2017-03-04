#pragma once

#include "Model.h"
#include "Render.h"

#include <SFML/Graphics.hpp>

class Controller {
public:
	Controller(Model*, Render*);
	~Controller();

	void inputs();

private:
	Model* model;
	Render* view;

	Inputable* inputTo;

	bool prevSpacePressed = false;
	bool prevMenuPressed = false;
};


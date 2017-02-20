#pragma once

#include "Updatable.h"
#include "Renderable.h"

class Entity : public Updatable, public Renderable {
public:
	Entity(int, int, int, int);
	~Entity();
};


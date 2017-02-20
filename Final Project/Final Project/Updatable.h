#pragma once

#include "WorldObject.h"

class Updatable : public virtual WorldObject {
public:
	virtual void update(float) = 0;
};
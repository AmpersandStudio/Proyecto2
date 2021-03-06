#pragma once
#include "checkML.h"

class Level;

class Layer
{
public:
	virtual void render() = 0;
	virtual void update(Level* pLevel) = 0;

	virtual ~Layer() {}

	inline void setActive(bool b) { active_ = b; }

protected:
	bool active_;
};


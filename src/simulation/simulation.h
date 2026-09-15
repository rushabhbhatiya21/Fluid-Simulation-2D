#pragma once

#include "grid.h"

class Simulation
{
public:
	Simulation();
	~Simulation();

	void initialize();
	Grid& getGrid();
	void update(float dt);

private:
	Grid current;
	Grid next;

	float D = 1.0f;
	float h = 1.0f;
};
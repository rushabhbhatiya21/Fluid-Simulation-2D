#pragma once

#include "grid.h"

class Simulation
{
public:
	Simulation();
	~Simulation();

	void initialize();
	Grid& getGrid();

private:
	Grid grid;
};
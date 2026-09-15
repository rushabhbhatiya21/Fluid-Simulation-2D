#pragma once

#include "grid.h"

class Simulation
{
public:
	Simulation();
	~Simulation();

	void initialize();
	Grid& getGrid();
	void update();

private:
	Grid grid;
	int yy = 60, xx = 60;
};
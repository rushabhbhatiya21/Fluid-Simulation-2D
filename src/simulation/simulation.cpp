#include "simulation.h"

Simulation::Simulation()
{
}

Simulation::~Simulation()
{
}

void Simulation::initialize()
{
	for (int y = 60; y < 68; y++)
	{
		for (int x = 60; x < 68; x++)
		{
			grid.set(x, y, 1.0f);
		}
	}
}

Grid& Simulation::getGrid()
{
	return grid;
}

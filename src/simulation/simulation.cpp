#include "simulation.h"
#include <iostream>

Simulation::Simulation()
{
}

Simulation::~Simulation()
{
}

void Simulation::initialize()
{
	for (int y = yy; y < yy + 8; y++)
	{
		for (int x = xx; x < xx + 8; x++)
		{
			grid.set(x, y, 1.0f);
		}
	}
}

Grid& Simulation::getGrid()
{
	return grid;
}

void Simulation::update()
{
	grid.clear();

	if (xx + 8 > 128)
		xx = -1;

	xx++;

	for (int y = yy; y < yy + 8; y++)
	{
		for (int x = xx; x < xx + 8; x++)
		{
			grid.set(x, y, 1.0f);
		}
	}
}

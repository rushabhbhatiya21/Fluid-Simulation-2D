#include "simulation.h"
#include <iostream>
#include <assert.h>

Simulation::Simulation()
{
}

Simulation::~Simulation()
{
}

void Simulation::initialize()
{
	//for (int y = 0; y < W; y++)
	//{
	//	for (int x = 0; x < H; x++)
	//	{
	//		current.set(x, y, 1.0f);
	//	}
	//}
	current.set(64, 64, 10.0f);
	current.set(63, 64, 10.0f);
	current.set(64, 63, 10.0f);
	current.set(63, 63, 10.0f);
}

Grid& Simulation::getGrid()
{
	return current;
}

void Simulation::update(float dt)
{
	// stability check
	assert(D * dt / (h * h) <= 0.25f);

	for (int y = 0; y < current.h; y++)
	{
		for (int x = 0; x < current.w; x++)
		{
			float currentValue = current.get(x, y);

			// boundary condition - no flux
			float neighborSum = current.getNeighbor(x - 1, y) + current.getNeighbor(x, y + 1) + current.getNeighbor(x + 1, y) + current.getNeighbor(x, y - 1);
			float laplacian = (neighborSum - 4 * currentValue) / (h * h);
			next.set(x, y, currentValue + (D * dt * laplacian));
		}
	}

	std::swap(current, next);
}

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
	equilibrium = false;
}

Grid& Simulation::getGrid()
{
	return current;
}

void Simulation::update(float dt)
{
	// stability check
	assert(D * dt / (h * h) <= 0.25f);

	if (equilibrium)
	{
		std::cout << "Equilibrium reached!" << std::endl;
		return;
	}

	maxValue = 0.0f;

	for (int y = 0; y < current.h; y++)
	{
		for (int x = 0; x < current.w; x++)
		{
			float currentValue = current.get(x, y);

			// boundary condition - no flux
			float neighborSum = current.getNeighbor(x - 1, y) + current.getNeighbor(x, y + 1) + current.getNeighbor(x + 1, y) + current.getNeighbor(x, y - 1);
			float laplacian = (neighborSum - 4 * currentValue) / (h * h);
			float newValue = currentValue + (D * dt * laplacian);
			next.set(x, y, newValue);

			maxValue = std::max(maxValue, abs(newValue - currentValue));
		}
	}

	std::swap(current, next);

	if (maxValue < tolerance)
		equilibrium = true;

	//std::cout << "max=" << maxValue << std::endl;
}

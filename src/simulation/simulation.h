#pragma once

#include "grid.h"

class Simulation
{
public:
	Simulation();
	~Simulation();

	void initialize();
	Grid& getGrid();
	void step();
	float totalScalar() const;
	float calculateFinalAbsolute() const;
	float calculateFinalRelative() const;
	bool getEquilibrium() const;
	float getSimulationTime() const;

private:
	Grid current;
	Grid next;

	float dt = 0.1f;
	float D = 1.0f;
	float h = 1.0f;
	float simulationTime = 0.0f;
	float tolerance = 0.000001f;
	bool equilibrium = false;
	float maxValue = 0;

	float initialTotal = 0.0f;
	float finalTotal = 0.0f;
};
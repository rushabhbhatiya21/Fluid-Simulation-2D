#include <iostream>
#include <simulation/simulation.h>
#include <platform/renderer.h>

int main()
{
	Simulation simulation;
	Renderer renderer;

	simulation.initialize();

	std::cout << "Initial total=" << simulation.totalScalar() << std::endl;

	int n = 0;
	bool printFinalErrors = true;

	while (!renderer.shouldClose())
	{
		if (n % 500 == 0)
			std::cout << "Step=" << n << ", total=" << simulation.totalScalar() << std::endl;

		std::cout << "Step=" << n << " SimulationTime=" << simulation.getSimulationTime() << std::endl;

		simulation.step();
		renderer.upload(simulation.getGrid().data());
		renderer.render();

		n++;

		if (simulation.getEquilibrium() && printFinalErrors)
		{
			std::cout << "Final Absolute Error=" << simulation.calculateFinalAbsolute() << std::endl;
			std::cout << "Final Relative Error=" << simulation.calculateFinalRelative() << std::endl;
			printFinalErrors = false;
		}
	}

	return 0;
} 
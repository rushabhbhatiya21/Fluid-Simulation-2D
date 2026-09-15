#include <iostream>
#include <simulation/simulation.h>
#include <platform/renderer.h>

int main()
{
	Simulation simulation;
	Renderer renderer;

	simulation.initialize();

	while (!renderer.shouldClose())
	{
		simulation.update();
		renderer.upload(simulation.getGrid().data());
		renderer.render();
	}


	return 0;
} 
#include <iostream>
#include <simulation/simulation.h>
#include <platform/renderer.h>

int main()
{
	Simulation simulation;
	Renderer renderer;

	simulation.initialize();
	//std::cout << simulation.getGrid().get(63, 63) << '\n';
	//std::cout << simulation.getGrid().get(0, 0) << '\n';

	return 0;
} 
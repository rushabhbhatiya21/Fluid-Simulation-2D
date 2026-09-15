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
		float before = 0.f, after = 0.f;
		for (int y = 0; y < 128; y++)
		{
			for (int x = 0; x < 128; x++)
			{
				before += simulation.getGrid().get(x, y);
			}
		}

		simulation.update(0.1f);
		renderer.upload(simulation.getGrid().data());
		renderer.render();

		for (int y = 0; y < 128; y++)
		{
			for (int x = 0; x < 128; x++)
			{
				after += simulation.getGrid().get(x, y);
			}
		}

		std::cout << "Before: " << before << '\n';
		std::cout << "After:  " << after << '\n';
	}

	return 0;
} 
#include "Renderer.h"
#include "Vector2.h"
#include "Input.h"
#include "Particle.h"
#include "Random.h"
#include "ETime.h"
#include <SDL.h>
#include <iostream>
#include <vector>
	
int main(int argc, char* argv[])
{
	// create systems
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Game Engine", 800, 600);

	Input input;
	input.Initialize();

	Time time;

	std::vector<Particle> particles;

	/*for (int i = 0; i < 0; i++)
	{
		particles.push_back(Particle{ {rand() % 800, rand() % 600}, { randomf(100, 300), 0.0}});
	}*/

	//main loop
	bool quit = false;
	while (!quit)
	{
		time.Tick();
		//std::cout << time.GetTime() << std::endl;

		//INPUT
		input.Update();

		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		//UPDATE
		Vector2 mousePosition = input.GetMousePosition();
		if (input.GetMouseButtonDown(0))
		{
			particles.push_back(Particle{ {mousePosition}, { randomf(-300, 300), randomf(-300, 300)}, randomf(1, 5)});
		}

		for (Particle& particle : particles)
		{
			particle.Update(time.GetDeltaTime());
			/*if (particle.position.x > 800) particle.position.x = 0;
			if (particle.position.x < 0) particle.position.x = 800;*/
		}

		//DRAW
		// clear screen
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();

		renderer.SetColor(255, 255, 255, 0);

		for (Particle particle : particles)
		{
			particle.Draw(renderer);
		}

		// show screen
		renderer.EndFrame();
	}

	return 0;
}
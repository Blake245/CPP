#include "../Engine/Source/Renderer.h"
#include "../Engine/Source/Vector2.h"
#include "../Engine/Source/Input.h"

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

	Vector2 v1{ 400,300 };
	Vector2 v2{ 600,500 };

	std::vector<Vector2> points;
	/*for (int i = 0; i < 100; i++) 
	{
		points.push_back(Vector2{ rand() % 800, rand() % 600 });
	}*/

	//main loop
	bool quit = false;
	while (!quit)
	{
		//input
		//update
		//draw

		//INPUT
		input.Update();

		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		//UPDATE
		Vector2 mousePosition = input.GetMousePosition();
		//std::cout << mousePosition.x << " " << mousePosition.y << std::endl;

		if (input.GetMouseButtonDown(0) && !input.GetPrevMouseButtonDown(0))
		{
			std::cout << "mouse pressed\n";
			points.push_back(mousePosition);
		}
		if (input.GetMouseButtonDown(0) && input.GetPrevMouseButtonDown(0))
		{
			float distance = (points.back() - mousePosition).Length();
			if(distance > 25) points.push_back(mousePosition);
		}

		/*Vector2 speed{ 0.5f, -0.1f };
		for (Vector2& point : points)
		{
			point = point + 0.002f;
		}*/

		//DRAW
		// clear screen
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();

		// draw cube
		renderer.SetColor(255, 255, 255, 0);

		/*renderer.DrawLine(200, 400, 500, 400);
		renderer.DrawLine(500, 400, 500, 200);
		renderer.DrawLine(500, 200, 200, 200);
		renderer.DrawLine(200, 200, 200, 400);

		renderer.DrawLine(200, 400, 250, 350);
		renderer.DrawLine(500, 400, 550, 350);
		renderer.DrawLine(250, 350, 550, 350);

		renderer.DrawLine(200, 200, 250, 150);
		renderer.DrawLine(500, 200, 550, 150);
		renderer.DrawLine(250, 150, 550, 150);
		
		renderer.DrawLine(550, 350, 550, 150);
		renderer.DrawLine(250, 350, 250, 150);*/

		//renderer.DrawLine(v1.x, v1.y, v2.x, v2.y);

		for (int i = 0; points.size() > 1 && i < points.size() - 1; i++)
		{
			renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
		}

		// Random Lines
		/*for (int i = 0; i < 100; i++)
		{
			renderer.SetColor(rand() % 255, rand() % 255, rand() % 255, 0);
			renderer.DrawPoint(rand() % 800, rand() % 600);
			renderer.SetColor(rand() % 255, rand() % 255, rand() % 255, 0);
			renderer.DrawLine(rand() % 800, rand() % 600, rand() % 800, rand() % 600);
		}*/
		// show screen
		renderer.EndFrame();
	}

	return 0;
}
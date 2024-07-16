#include "Engine.h"
#include "../../Source/Player.h"
#include "../../Source/Enemy.h"
#include"Scene.h"

#include <iostream>
#include <vector>
	
int main(int argc, char* argv[])
{
	g_engine.Initialize();

	// create systems

	Time time;

	//create audio system
	g_engine.GetAudio().AddSound("bass.wav");
	g_engine.GetAudio().AddSound("snare.wav");
	g_engine.GetAudio().AddSound("open-hat.wav");
	g_engine.GetAudio().AddSound("close-hat.wav");
	g_engine.GetAudio().AddSound("clap.wav");
	g_engine.GetAudio().AddSound("cowbell.wav");
	std::vector<Particle> particles;
	float offset = 0;

		// Models
	std::vector<Vector2> points;
	points.push_back(Vector2{ 5, 0 });
	points.push_back(Vector2{ -5, -5 });
	points.push_back(Vector2{ -5, 5 });
	points.push_back(Vector2{ 5, 0 });


	// actor
	Model* model = new Model{ points, Color{ 1, 0, 0 } };

	Scene* scene = new Scene();

	Transform transform({400, 300}, 0, 5);
	Player* player = new Player(800, transform, model);
	player->SetDamping(2.0f);
	scene->AddActor(player);

	Model* enemyModel = new Model{ points, Color{ 1, 0, 1 } };
	auto enemy = new Enemy(1000, Transform{ {300, 300}, 0, 2 }, enemyModel);
	scene->AddActor(enemy);

	//main loop
	bool quit = false;
	while (!quit)
	{
		time.Tick();
		//std::cout << time.GetTime() << std::endl;

		//INPUT
		g_engine.GetInput().Update();

		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		//audio input
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_B) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_B))
		{
			//bass
			g_engine.GetAudio().PlaySound("bass.wav");
		}
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_V) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_V))
		{
			//snare
			g_engine.GetAudio().PlaySound("snare.wav");
		}
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_N) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_N))
		{
			//open hat
			g_engine.GetAudio().PlaySound("open-hat.wav");
		}
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_H) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_H))
		{
			//close hat
			g_engine.GetAudio().PlaySound("close-hat.wav");
		}
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_C) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_C))
		{
			//clap
			g_engine.GetAudio().PlaySound("clap.wav");
		}
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_G) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_G))
		{
			//cowbell
			g_engine.GetAudio().PlaySound("cowbell.wav");
		}

		//Model Movement
			//input:velocity +-= speed
		/*float thrust = 0;
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_LEFT)) transform.rotation += Math::DegToRad(-100) * time.GetDeltaTime();
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_RIGHT)) transform.rotation += Math::DegToRad(100) * time.GetDeltaTime();;
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_UP)) thrust = 400;
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_DOWN)) thrust = -400;*/
		
		/*Vector2 velocity = Vector2{thrust, 0.0f}.Rotate(transform.rotation);
		transform.position += velocity * time.GetDeltaTime();*/
		/*transform.position.x - Math::Wrap(transform.position.x, (float)renderer.getWidth());
		transform.position.y - Math::Wrap(transform.position.y, (float)renderer.getHeight());*/

		//transform.rotation = transform.rotation + time.GetDeltaTime();
		//UPDATE
		scene->Update(time.GetDeltaTime());

		Vector2 mousePosition = g_engine.GetInput().GetMousePosition();
		if (g_engine.GetInput().GetMouseButtonDown(0))
		{
			particles.push_back(Particle{ {mousePosition}, randomOnUnitCircle() * randomf(10, 200), randomf(1, 3)});
		}

		for (Particle& particle : particles)
		{
			particle.Update(time.GetDeltaTime());
			if (particle.position.x > 800) particle.position.x = 0;
			if (particle.position.x < 0) particle.position.x = 800;
		}

		//audio
		//g_engine.GetAudio().update();

		//DRAW
		// clear screen
		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();

		//draw circle
		g_engine.GetRenderer().SetColor(255, 255, 255, 0);
		float radius = 200;
		offset += (90 * time.GetDeltaTime());
		for (float angle = 0; angle < 360; angle += 360 / 120)
		{
			float x = Math::Cos(Math::DegToRad(angle + offset)) * Math::Sin(offset * 0.01f + angle) * radius;
			float y = Math::Sin(Math::DegToRad(angle + offset)) * Math::Sin(offset * 0.01f + angle) * radius;

			g_engine.GetRenderer().SetColor(random(256), random(256), random(256), 0);
			//g_engine.GetRenderer().DrawRect(x + 400, y + 300, randomf(1, 4), randomf(1, 4));
		}

		// draw particle
		g_engine.GetRenderer().SetColor(255, 255, 255, 0);

		for (Particle particle : particles)
		{
			particle.Draw(g_engine.GetRenderer());
		}

		//draw model
		scene->Draw(g_engine.GetRenderer());

		// show screen
		g_engine.GetRenderer().EndFrame();
	}

	return 0;
}
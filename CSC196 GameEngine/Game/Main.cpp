#include "Engine.h"
#include "../../Source/Player.h"
#include "../../Source/Enemy.h"
#include "../../Source/GameData.h"
#include "../../Source/SpaceGame.h"
#include "Scene.h"
#include "Font.h"
#include "Text.h"

#include <iostream>
#include <vector>
	
int main(int argc, char* argv[])
{
	g_engine.Initialize();

	//Font* font = new Font();
	//font->Load("Nightmare Codehack.otf", 200);
	//font->Load("Arcade.ttf", 200);

	//Text* text = new Text(font);
	//text->Create(g_engine.GetRenderer(), "Hello World", Color{ 1, 1, 1, 1 });

	SpaceGame* game = new SpaceGame(&g_engine);
	game->Initialize();

	while (!g_engine.isQuit())
	{
		g_engine.Update();
		game->Update(g_engine.GetTime().GetDeltaTime());

		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();

		//text->Draw(g_engine.GetRenderer(), 40, 40);

		game->Draw(g_engine.GetRenderer());

		g_engine.GetRenderer().EndFrame();
	}

	return 0;
}

/*
	//create audio system
	g_engine.GetAudio().AddSound("bass.wav");
	g_engine.GetAudio().AddSound("snare.wav");
	g_engine.GetAudio().AddSound("open-hat.wav");
	g_engine.GetAudio().AddSound("close-hat.wav");
	g_engine.GetAudio().AddSound("clap.wav");
	g_engine.GetAudio().AddSound("cowbell.wav");
	std::vector<Particle> particles;
	float offset = 0;

	// actor
	Model* model = new Model{ GameData::shipPoints, Color{ 1, 0, 0 } };

	Scene* scene = new Scene();

	Transform transform({400, 300}, 0, 3);
	Player* player = new Player(800, transform, model);
	player->SetDamping(2.0f);
	player->SetTag("Player");
	scene->AddActor(player);

	float spawnTimer = 2.0f;

	//main loop
	while (!g_engine.isQuit())
	{
		g_engine.Update();

		spawnTimer -= g_engine.GetTime().GetDeltaTime();
		if (spawnTimer <= 0)
		{
			Model* enemyModel = new Model{ GameData::shipPoints, Color{ 1, 0, 1 } };
			auto enemy = new Enemy(400, Transform{ {random(0, g_engine.GetRenderer().getWidth()), random(0,g_engine.GetRenderer().getHeight())}, 0, 2}, enemyModel);
			enemy->SetDamping(1.0f);
			enemy->SetTag("Enemy");
			scene->AddActor(enemy);

			spawnTimer = 2;
		}

		//UPDATE
		scene->Update(g_engine.GetTime().GetDeltaTime());

		Vector2 mousePosition = g_engine.GetInput().GetMousePosition();
		if (g_engine.GetInput().GetMouseButtonDown(0))
		{
			particles.push_back(Particle{ {mousePosition}, randomOnUnitCircle() * randomf(10, 200), randomf(1, 3)});
		}

		for (Particle& particle : particles)
		{
			particle.Update(g_engine.GetTime().GetDeltaTime());
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
		offset += (90 * g_engine.GetTime().GetDeltaTime());
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
*/
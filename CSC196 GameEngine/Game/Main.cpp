#include "Renderer.h"
#include "Vector2.h"
#include "Input.h"
#include "Particle.h"
#include "Random.h"
#include "ETime.h"
#include "MathUtils.h"
#include "Model.h"
#include "Transform.h"

#include <SDL.h>
#include <iostream>
#include <vector>
#include <fmod.hpp>
	
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
	float offset = 0;

		// create audio system
	FMOD::System* audio;
	FMOD::System_Create(&audio);
	void* extradriverdata = nullptr;
	audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

		// Models
	std::vector<Vector2> points;
	points.push_back(Vector2{ 5, 0 });
	points.push_back(Vector2{ -5, -5 });
	points.push_back(Vector2{ -5, 5 });
	points.push_back(Vector2{ 5, 0 });
	Model model{ points, Color{1,0,0} };

	//>> 1 = /2
	Transform transform({ renderer.getWidth() >> 1, renderer.getHeight() >> 1}, 0, 5);


	//play audio when program start
	FMOD::Sound* sound = nullptr;
	/*audio->createSound("test.wav", FMOD_DEFAULT, 0, &sound);
	audio->playSound(sound, 0, false, nullptr);*/
	std::vector<FMOD::Sound*> sounds;
	audio->createSound("bass.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);
	audio->createSound("snare.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);
	audio->createSound("open-hat.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);
	audio->createSound("close-hat.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);
	audio->createSound("clap.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);
	audio->createSound("cowbell.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);
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

		//audio input
		if (input.GetKeyDown(SDL_SCANCODE_B) && !input.GetPrevKeyDown(SDL_SCANCODE_B))
		{
			//bass
			audio->playSound(sounds[0], 0, false, nullptr);
		}
		if (input.GetKeyDown(SDL_SCANCODE_V) && !input.GetPrevKeyDown(SDL_SCANCODE_V))
		{
			//snare
			audio->playSound(sounds[1], 0, false, nullptr);
		}
		if (input.GetKeyDown(SDL_SCANCODE_N) && !input.GetPrevKeyDown(SDL_SCANCODE_N))
		{
			//open hat
			audio->playSound(sounds[2], 0, false, nullptr);
		}
		if (input.GetKeyDown(SDL_SCANCODE_H) && !input.GetPrevKeyDown(SDL_SCANCODE_H))
		{
			//close hat
			audio->playSound(sounds[3], 0, false, nullptr);
		}
		if (input.GetKeyDown(SDL_SCANCODE_C) && !input.GetPrevKeyDown(SDL_SCANCODE_C))
		{
			//clap
			audio->playSound(sounds[4], 0, false, nullptr);
		}
		if (input.GetKeyDown(SDL_SCANCODE_G) && !input.GetPrevKeyDown(SDL_SCANCODE_G))
		{
			//cowbell
			audio->playSound(sounds[5], 0, false, nullptr);
		}

		//Model Movement
			//input:velocity +-= speed
		float thrust = 0;
		if (input.GetKeyDown(SDL_SCANCODE_LEFT)) transform.rotation += Math::DegToRad(- 100) * time.GetDeltaTime();
		if (input.GetKeyDown(SDL_SCANCODE_RIGHT)) transform.rotation += Math::DegToRad(100) * time.GetDeltaTime();;
		if (input.GetKeyDown(SDL_SCANCODE_UP)) thrust = 400;
		if (input.GetKeyDown(SDL_SCANCODE_DOWN)) thrust = -400;
		
		Vector2 velocity = Vector2{thrust, 0.0f}.Rotate(transform.rotation);
		transform.position += velocity * time.GetDeltaTime();
		/*transform.position.x - Math::Wrap(transform.position.x, (float)renderer.getWidth());
		transform.position.y - Math::Wrap(transform.position.y, (float)renderer.getHeight());*/

		//transform.rotation = transform.rotation + time.GetDeltaTime();
		//UPDATE
		Vector2 mousePosition = input.GetMousePosition();
		if (input.GetMouseButtonDown(0))
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
		audio->update();

		//DRAW
		// clear screen
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();

		//draw circle
		/*renderer.SetColor(255, 255, 255, 0);
		float radius = 200;
		offset += (90 * time.GetDeltaTime());
		for (float angle = 0; angle < 360; angle += 360 / 120)
		{
			float x = Math::Cos(Math::DegToRad(angle + offset)) * Math::Sin(offset * 0.01f + angle) * radius;
			float y = Math::Sin(Math::DegToRad(angle + offset)) * Math::Sin(offset * 0.01f + angle) * radius;

			renderer.SetColor(random(256), random(256), random(256), 0);
			renderer.DrawRect(x + 400, y + 300, randomf(1, 4), randomf(1, 4));
		}*/

		// draw particle
		renderer.SetColor(255, 255, 255, 0);

		for (Particle particle : particles)
		{
			particle.Draw(renderer);
		}

		//draw model
		model.Draw(renderer, transform);

		// show screen
		renderer.EndFrame();
	}

	return 0;
}
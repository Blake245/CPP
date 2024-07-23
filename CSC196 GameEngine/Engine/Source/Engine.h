#pragma once
#include "Renderer.h"
#include "Audio.h"
#include "Input.h"

#include "Vector2.h"
#include "Particle.h"
#include "Random.h"

#include "ETime.h"
#include "MathUtils.h"
#include "Model.h"
#include "Transform.h"

#include <SDL.h>
#include <fmod.hpp>

#define RENDERER g_engine.GetRenderer()

class Engine
{
public:
	Engine() = default;
	~Engine() = default;

	bool Initialize();
	void Shutdown();

	void Update();

	Renderer& GetRenderer() { return *m_renderer; }
	Input& GetInput() { return *m_input; }
	Audio& GetAudio() { return *m_audio; }
	Time& GetTime() { return *m_time; }
	bool isQuit() { return quit; }
private:
	bool quit{ false };

	Time* m_time{ nullptr };
	Renderer* m_renderer{ nullptr };
	Input* m_input{ nullptr };
	Audio* m_audio{ nullptr };
};
//extern same as inline
extern Engine g_engine;



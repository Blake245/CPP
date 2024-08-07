#include "Player.h"
#include "Engine.h"
#include "Bullet.h"
#include "Scene.h"
#include "GameData.h"
#include "SpaceGame.h"
#include "Audio.h"
#include <iostream>


void Player::Update(float dt)
{
	//movement
	float thrust = 0;
	/*if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_A)) m_transform.rotation += Math::DegToRad(-100) * dt;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_D)) m_transform.rotation += Math::DegToRad(100) * dt;
	*/
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_D)) thrust = m_speed;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_A)) thrust = -m_speed;

	Vector2 acceleration = Vector2{ thrust, 0.0f };//.Rotate(m_transform.rotation); //* thrust;
	m_velocity += acceleration * dt;

	m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().getWidth());
	m_transform.position.y = Math::Wrap(m_transform.position.y, (float)g_engine.GetRenderer().getHeight());

	//fire
	m_fireTimer -= dt;
	m_powerupTimer -= dt;
	if ((g_engine.GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && m_fireTimer <= 0) 
		&& !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_SPACE))
	{
		m_fireTimer = 0.25 * m_fireModifier;
		g_engine.GetAudio().PlaySound("Lazer.wav");
		
		// shoot at mouse position
		/*Vector2 direction = g_engine.GetInput().GetMousePosition() - m_transform.position;
		float angle = direction.Angle();*/

		// actor
		if (!m_fireSpread)
		{
			Model* model = new Model{ GameData::bulletPoints, Color{ 1, 1, 1 } };
			Transform transform{ m_transform.position, m_transform.rotation, 1.0f };

			auto bullet = std::make_unique<Bullet>(400, transform, model);
			bullet->SetLifespan(2);
			bullet->SetTag("PlayerBullet");
			m_scene->AddActor(std::move(bullet));
		}
		else 
		{
			m_spreadAngle = Math::DegToRad(350);
			for (int i = 0; i < 3; i++)
			{
				
				Model* model = new Model{ GameData::bulletPoints, Color{ 1, 1, 1 } };
				Transform transform{ m_transform.position, m_transform.rotation + m_spreadAngle, 1.0f };

				auto bullet = std::make_unique<Bullet>(400, transform, model);
				bullet->SetLifespan(2);
				bullet->SetTag("PlayerBullet");
				m_scene->AddActor(std::move(bullet));
				m_spreadAngle += Math::DegToRad(10);
				
			}
		}
	}
	if (m_powerupTimer <= 0) m_fireSpread = false;

	Actor::Update(dt);
}

void Player::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Enemy")
	{
		//m_destroyed = true;
		g_engine.GetAudio().PlaySound("Hit_Hurt2.wav");
		dynamic_cast<SpaceGame*>(m_scene->GetGame())->OnPlayerDeath();
	}
}

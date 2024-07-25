#include "EnemyShooter.h"
#include "Player.h"
#include "Scene.h"
#include "Game.h"
#include "Engine.h"
#include "Pickup.h"
#include "GameData.h"
#include "Bullet.h"
#include "MathUtils.h"

void EnemyShooter::Update(float dt)
{
	Player* player = m_scene->GetActor<Player>();
	if (player)
	{
		//m_directionStart = randomf(1, 100);
		if (m_directionStart > 50)
		{
			m_transform.position.x += m_speed * dt;
		}
		else
		{
			m_transform.position.x -= m_speed * dt;
		}
		
		m_transform.position.y += (m_speed / 3) * dt;
		m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().getWidth());
		m_fireTimer -= dt;

		if (m_fireTimer <= 0)
		{
			Model* model = new Model{ GameData::bulletPoints, Color{ 1, 0, 0 } };
			Transform transform{ m_transform.position, m_transform.rotation, 1.0f };
			auto bullet = std::make_unique<Bullet>(400, transform, model);
			bullet->SetLifespan(2);
			bullet->SetTag("Enemy");
			m_scene->AddActor(std::move(bullet));
			m_fireTimer = 2;
		}
	}
	if (m_transform.position.x >= g_engine.GetRenderer().getWidth())
	{
		m_speed = -m_speed;
	}
	if (m_transform.position.y > g_engine.GetRenderer().getHeight())
	{
		m_destroyed = true;
	}

	Actor::Update(dt);
}

void EnemyShooter::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Player" || actor->GetTag() == "PlayerBullet")
	{
		m_pickupChance = randomf();
		if (m_pickupChance <= 0.1f)
		{
			Model* pickupModel = new Model{ GameData::healthPickup, Color{ 0, 1, 0 } };
			auto healthPickup = std::make_unique<Pickup>(100.0f, Transform{ { m_transform.position }, 0, 10 }, pickupModel);
			healthPickup->SetTag("HealthPickup");
			m_scene->AddActor(std::move(healthPickup));
		}
		m_pickupChance = randomf();
		if (m_pickupChance <= 0.2f && m_pickupChance > 0.1f)
		{
			Model* pickupModel = new Model{ GameData::spreadPickup, Color{ 1, 0, 0 } };
			auto spreadPickup = std::make_unique<Pickup>(100.0f, Transform{ { m_transform.position }, 0, 10 }, pickupModel);
			spreadPickup->SetTag("SpreadPickup");
			m_scene->AddActor(std::move(spreadPickup));
		}
		m_scene->GetGame()->AddPoints(100);
		m_destroyed = true;
		g_engine.GetAudio().PlaySound("Explosion6.wav");

	}
}

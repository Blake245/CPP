#include "Enemy.h"
#include "Player.h"
#include "Scene.h"
#include "Game.h"
#include "Engine.h"
#include "Pickup.h"
#include "GameData.h"

void Enemy::Update(float dt)
{
	Player* player = m_scene->GetActor<Player>();
	if (player)
	{
		Vector2 direction = Vector2{ m_transform.position.x, 800.0f } - m_transform.position;
		m_velocity += direction.Normalized() * m_speed * dt;
		m_transform.rotation = direction.Angle();
	}
	if (m_transform.position.y > g_engine.GetRenderer().getHeight())
	{
		m_destroyed = true;
	}
	
	Actor::Update(dt);
}

void Enemy::OnCollision(Actor* actor)
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

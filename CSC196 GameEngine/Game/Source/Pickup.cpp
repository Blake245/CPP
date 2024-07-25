#include "Pickup.h"
#include "Player.h"
#include "Scene.h"
#include "SpaceGame.h"
#include "Engine.h"

void Pickup::Update(float dt)
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

void Pickup::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Player" && m_tag == "HealthPickup")
	{
		//dynamic_cast<Player*>(actor)->SetFireModifier(0.5f);
		dynamic_cast<SpaceGame*>(m_scene->GetGame())->AddHealth();
		g_engine.GetAudio().PlaySound("HealthUp.wav");
		m_destroyed = true;
	}
	if (actor->GetTag() == "Player" && m_tag == "SpreadPickup")
	{
		dynamic_cast<Player*>(actor)->SetFireSpread(true);
		g_engine.GetAudio().PlaySound("AttackUp.wav");
		m_destroyed = true;
	}
}

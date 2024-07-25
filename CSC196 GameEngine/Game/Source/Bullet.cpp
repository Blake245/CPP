#include "Bullet.h"
#include "Engine.h"

void Bullet::Update(float dt)
{
	// create particle trail
	Particle::Data data
	{
		m_transform.position,
		Vector2{1, 0}.Rotate(randomf(Math::Pi)) * 50,
		randomf(0.1f, 0.2f),
		255, 176, 16, 0
	};
	g_engine.GetPS().AddParticle(data);

	m_velocity = Vector2{ 1, 0 }.Rotate(m_transform.rotation) * m_speed;
	Actor::Update(dt);

	//m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().getWidth());
	//m_transform.position.y = Math::Wrap(m_transform.position.y, (float)g_engine.GetRenderer().getHeight());
}

void Bullet::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Enemy" && m_tag != "Enemy")
	{
		m_destroyed = true;
	}
	if (actor->GetTag() == "Player" && m_tag == "Enemy")
	{
		m_destroyed = true;
	}
}

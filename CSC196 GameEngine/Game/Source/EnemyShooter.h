#pragma once
#include "Enemy.h"
#include "Actor.h"
#include "Engine.h"
class EnemyShooter : public Actor
{
public:
	EnemyShooter() = default;
	EnemyShooter(const Transform& transform) : Actor{ transform } {}
	EnemyShooter(const Transform& transform, Model* model) :
		Actor{ transform, model }
	{}
	EnemyShooter(float speed, const Transform& transform, Model* model) :
		Actor{ transform, model },
		m_speed{ speed }
	{ m_directionStart = randomf(1, 100); }

	void Update(float dt);
	virtual void OnCollision(Actor* actor);

private:
	float m_speed = 0;
	float m_fireTimer = 0;
	float m_pickupChance = 0;
	float m_directionStart = 0;
};

#pragma once
#include "Actor.h"

class Player : public Actor
{
public:
	Player() = default;
	Player(const Transform& transform) : Actor{ transform } {}
	Player(const Transform& transform, Model* model) :
		Actor{ transform, model }
	{}
	Player(float speed, const Transform& transform, Model* model) :
		Actor{ transform, model },
		m_speed{speed}
	{}

	void Update(float dt);
	void OnCollision(Actor* actor);

	void SetFireModifier(float modifier) { m_fireModifier = modifier; }
	void SetFireSpread(bool isTrue) 
	{ 
		m_fireSpread = isTrue; 
		m_powerupTimer = 5;
	}
private:
	float m_speed = 0;
	float m_fireTimer = 0;
	float m_fireModifier = 1;
	bool m_fireSpread = false;
	float m_spreadAngle = 0;
	float m_powerupTimer{ 0 };
};

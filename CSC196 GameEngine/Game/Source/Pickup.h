#pragma once
#include "Actor.h"

class Pickup : public Actor
{
public:
	Pickup() = default;
	Pickup(const Transform& transform) : Actor{ transform } {}
	Pickup(const Transform& transform, Model* model) :
		Actor{ transform, model }
	{}
	Pickup(float speed, const Transform& transform, Model* model) :
		Actor{ transform, model },
		m_speed{ speed }
	{}
	void Update(float dt);
	void OnCollision(Actor* actor) override;
protected:
	float m_speed = 0;
};


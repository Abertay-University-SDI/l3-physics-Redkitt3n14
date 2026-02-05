#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"

class Sheep :
	public GameObject
{

public:
	Sheep();
	~Sheep();

	void handleInput(float dt) override;
	void update(float dt) override;

	void SetWorldSize(sf::Vector2f);

private:
	const float ACCELERATION = 20.0f;
	const float DRAG_FACTOR = 0.9f;
	sf::Vector2f m_acceleration;

	const float APPROX_ONE_OVER_ROOT_TWO = 0.70710678f;	// 1 / sqrt(2)

	sf::Vector2f m_worldSize;

	// animations
	Animation m_walkDown;
	Animation m_walkUp;
	Animation m_walkUpRight;
	Animation m_walkRight;
	Animation m_walkDownRight;

	Animation* m_currentAnimation;

};


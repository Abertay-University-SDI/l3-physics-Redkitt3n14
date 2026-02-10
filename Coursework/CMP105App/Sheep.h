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

	void collisionResponse(GameObject);

	void SetWorldSize(sf::Vector2f);
	sf::Vector2f checkWallAndBounce(sf::Vector2f);

private:
	const float ACCELERATION = 30.0f;
	const float DRAG_FACTOR = 0.97f;
	sf::Vector2f m_acceleration;
	const float COEFF_OF_RESTITUTION = 0.85f;

	sf::Vector2f m_worldSize;

	// animations
	Animation m_walkDown;
	Animation m_walkUp;
	Animation m_walkUpRight;
	Animation m_walkRight;
	Animation m_walkDownRight;

	Animation* m_currentAnimation;

};


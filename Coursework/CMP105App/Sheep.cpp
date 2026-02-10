#include "Sheep.h"

Sheep::Sheep()
{
	// initialise animations
	for (int i = 0; i < 4; i++)
		m_walkDown.addFrame({ { 64 * i, 0 }, { 64, 64 } });
	m_walkDown.setLooping(true);
	m_walkDown.setFrameSpeed(0.25f);

	for (int i = 0; i < 4; i++)
		m_walkUp.addFrame({ { (64 * (i + 4)), 0 }, { 64, 64 } });
	m_walkUp.setLooping(true);
	m_walkUp.setFrameSpeed(0.25f);

	for (int i = 0; i < 4; i++)
		m_walkUpRight.addFrame({ { 64 * i, 64 }, { 64, 64 } });
	m_walkUpRight.setLooping(true);
	m_walkUpRight.setFrameSpeed(0.25f);

	for (int i = 0; i < 4; i++)
		m_walkRight.addFrame({ { (64 * (i + 4)), 64 }, { 64, 64 } });
	m_walkRight.setLooping(true);
	m_walkRight.setFrameSpeed(0.25f);

	for (int i = 0; i < 4; i++)
		m_walkDownRight.addFrame({ { 64 * i, 128 }, { 64, 64 } });
	m_walkDownRight.setLooping(true);
	m_walkDownRight.setFrameSpeed(0.25f);

	// the next 4 animations go clockwise from Up through Right to Down.

	m_currentAnimation = &m_walkDown;
	setTextureRect(m_currentAnimation->getCurrentFrame());
}

Sheep::~Sheep()
{
}

void Sheep::handleInput(float dt)
{
	// set sheep direction

	// grab this to detect changes per frame for later
	sf::Vector2f input_dir;
	sf::Vector2f last_dir = input_dir;

	// sheep brake
	if (m_input->isKeyDown(sf::Keyboard::Scancode::Space))
	{
		input_dir = { 0,0 };
		return;
	}

	// Set 8-directional movement based on WASD
	if (m_input->isKeyDown(sf::Keyboard::Scancode::A))
	{
		input_dir.x = -1;

		if (m_input->isKeyDown(sf::Keyboard::Scancode::W))
		{
			input_dir.y = -1;
			m_currentAnimation = &m_walkUpRight;
			m_currentAnimation->setFlipped(true);
		}


		else if (m_input->isKeyDown(sf::Keyboard::Scancode::S))
		{
			input_dir.y = 1;
			m_currentAnimation = &m_walkDownRight;
			m_currentAnimation->setFlipped(true);
		}
		else
		{
			input_dir.y = 0;
			m_currentAnimation = &m_walkRight;
			m_currentAnimation->setFlipped(true);
		}

	}
	else if (m_input->isKeyDown(sf::Keyboard::Scancode::D))
	{
		input_dir.x = 1;

		if (m_input->isKeyDown(sf::Keyboard::Scancode::W))
		{
			input_dir.y = -1;
			m_currentAnimation = &m_walkUpRight;
			m_currentAnimation->setFlipped(false);
		}
		else if (m_input->isKeyDown(sf::Keyboard::Scancode::S))
		{
			input_dir.y = 1;
			m_currentAnimation = &m_walkDownRight;
			m_currentAnimation->setFlipped(false);
		}
		else
		{
			input_dir.y = 0;
			m_currentAnimation = &m_walkRight;
			m_currentAnimation->setFlipped(false);
		}

	}
	else
	{
		input_dir.x = 0;

		if (m_input->isKeyDown(sf::Keyboard::Scancode::W))
		{
			input_dir.y = -1;
			m_currentAnimation = &m_walkUp;

		}

		else if (m_input->isKeyDown(sf::Keyboard::Scancode::S))
		{
			input_dir.y = 1;
			m_currentAnimation = &m_walkDown;
		}
	}

	// normalise the diagonal movements
	if (input_dir.length() > 1) {
		input_dir = input_dir.normalized();
	}
	
	// sets acceleration
	m_acceleration = input_dir * ACCELERATION;

}

void Sheep::collisionResponse(GameObject collider)
{
	m_velocity *= -COEFF_OF_RESTITUTION;
	if (m_velocity.lengthSquared() < 200) {
		move(m_velocity * 0.5f);
	}
	else {
		move(m_velocity * 0.05f); // clear the zone
	}
}

void Sheep::update(float dt)
{
	setTextureRect(m_currentAnimation->getCurrentFrame());
	if (m_acceleration.x != 0 || m_acceleration.y != 0)
		m_currentAnimation->animate(dt);

	// caluclate movement needed for dt since last move
	move(m_velocity * dt);

	// check if there is a wall collision - inverts motion axis if so
	m_velocity = checkWallAndBounce(m_velocity);

	// move the sheep
	m_velocity = (m_velocity + (m_acceleration * 1.0f)) * DRAG_FACTOR;

}

void Sheep::SetWorldSize(sf::Vector2f sizeIn)
{
	m_worldSize = sizeIn;
}

sf::Vector2f Sheep::checkWallAndBounce(sf::Vector2f m_velocity) {

	sf::Vector2f pos = getPosition();

	if ((pos.x + getSize().x > m_worldSize.x) && (m_velocity.x > 0)) {
		m_velocity.x *= -COEFF_OF_RESTITUTION;
	}
	else if ((pos.x < 0) && (m_velocity.x < 0)) {
		m_velocity.x *= -COEFF_OF_RESTITUTION;
	}

	if ((pos.y + getSize().y > m_worldSize.y) && (m_velocity.y > 0)) {
		m_velocity.y *= -COEFF_OF_RESTITUTION;
	}
	else if ((pos.y < 0) && (m_velocity.y < 0)) {
		m_velocity.y *= -COEFF_OF_RESTITUTION;
	}

	return m_velocity;
}
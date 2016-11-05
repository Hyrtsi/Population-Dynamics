#include "stdafx.h"
#include "agent.hpp"
#include <iostream>

#define pi 3.1415926

Agent::Agent(float xPos, float yPos)
{

	_xPos = xPos;
	_yPos = yPos;
	_dir = 2 * pi * (rand() % 100) / 100.0f;

	_hasTarget = false;
	_movingToTarget = false;



	if (rand() % 100 > 5) {
		_isSick = false;
		_health = 255;
	}
	else {
		_isSick = true;
		_health = 4;
	}

	_state = wait;
	_state = walk;
}




void Agent::draw(sf::RenderWindow& window) {

	sf::CircleShape shape(radius);
	shape.setFillColor(sf::Color(255 - _health, _health, 20));
	shape.setPosition(_xPos, _yPos);
	window.draw(shape);
}


void Agent::step(const std::vector<Agent>& agents,
	const std::vector<std::vector<float>>& obstacleList) {

	if (_state == wait) {
		if (rand() % 1000 > 990) {
			_state = walk;
			_movingToTarget = true;
		}
	}
	else if (_state == walk) {
		move(agents, obstacleList);
		if (rand() % 1000 > 990) _state = wait;
	}

	updateHealth(agents);
}

void Agent::updateHealth(const std::vector<Agent>& agents) {

	float infectDistance = 40.0f;

	for (auto& agent : agents) {
		if (&agent == this)
			continue;

		float
			disToOther(sqrtf(pow(agent._xPos - _xPos, 2) + pow(agent._yPos - _yPos, 2))),
			dirToOther(atan2(agent._yPos - _yPos, agent._xPos - _xPos));

		if (disToOther < infectDistance) {
			if (agent._isSick) {
				_health -= ((rand() % 100) / 30.0f) * agent._health;
			}
		}
	}

	// Transforming healthy to sick

	if (_health < 5) {
		_isSick = true;
		_health = 4;
	}
}



void Agent::move(const std::vector<Agent>& agents,
	const std::vector<std::vector<float>>& obstacleList) {

	float minDistance = 20.0f;
	float infectDistance = 40.0f;
	float speed = 5.0f;
	float xMax = 800 - radius;
	float yMax = 600 - radius;


	// Target actions

	if (_hasTarget == false) {

		_xTarget = 800 * (rand() % 100) / 100;
		_yTarget = 600 * (rand() % 100) / 100;
		_hasTarget = true;

		_dir = pi * (rand() % 100) / 100;
	}

	if (_hasTarget == true && _movingToTarget == true) {
		float
			disToTarget(sqrtf(pow(_xTarget - _xPos, 2) + pow(_yTarget - _yPos, 2))),
			dirToTarget(atan2(_yTarget - _yPos, _xTarget - _xPos));

		if (disToTarget < speed * 5.0f) _hasTarget = false;

		_dir = dirToTarget;
	}



	// Collision check with other agents

	for (auto& agent : agents) {
		if (&agent == this)
			continue;

		float
			disToOther(sqrtf(pow(agent._xPos - _xPos, 2) + pow(agent._yPos - _yPos, 2))),
			dirToOther(atan2(agent._yPos - _yPos, agent._xPos - _xPos));

		if (disToOther < minDistance) {
			_dir += pi;
			_movingToTarget = false;
		}

	}

	// Collision check wrt window frames

	if (_dir > 2 * pi)
		_dir -= 2 * pi;
	if (_dir < 0)
		_dir += 2 * pi;

	float collisionOffset = pi * (rand() % 100) / 100.0f;

	if (_xPos<0+radius) {
		_dir += pi + collisionOffset;
		_xPos = 0 + radius;
	}
	if (_yPos<0+radius) {
		_dir += pi + collisionOffset;
		_yPos = 0 + radius;
	}
	if (_xPos>xMax) {
		_dir += pi + collisionOffset;
		_xPos = xMax - radius;
	}
	if (_yPos>yMax) {
		_dir += pi + collisionOffset;
		_yPos = yMax - radius;
	}

	// Some noise to the movement
	//_dir += pi / 2 * ((rand() % 100) - 50) / 100.0f;



	// Collision check wrt objects

	for (auto& obstacle : obstacleList) {

		float newx = _xPos + speed * cosf(_dir);
		float newy = _yPos + speed * sinf(_dir);

		// The obstacle params have to be finetuned !!

		bool collision = newx > obstacle[0]
			&& newx < obstacle[0] + obstacle[2]
			&& newy > obstacle[1]
			&& newy < obstacle[1] + obstacle[3];


		while (collision == true) {

			_movingToTarget = false;

			_dir += pi / 2;			// Proper value?

			if (_dir > 2 * pi)
				_dir -= 2 * pi;

			newx = _xPos + speed * cosf(_dir);
			newy = _yPos + speed * sinf(_dir);

			collision = newx > obstacle[0]
				&& newx < obstacle[0] + obstacle[2]
				&& newy > obstacle[1]
				&& newy < obstacle[1] + obstacle[3];
		}
	}

	// Update x, y

	_xPos += speed * cosf(_dir);
	_yPos += speed * sinf(_dir);
	
}


void Agent::setTarget(sf::Event& event) {

	if (event.type == sf::Event::MouseButtonPressed) {
		_xTarget = event.mouseButton.x;
		_yTarget = event.mouseButton.y;
		_movingToTarget = true;
	}

}
#include "stdafx.h"
#include "world.hpp"
#include <iostream>

World::World(unsigned int nAgents) { }


void World::addAgents(unsigned int nAgents) {



	for (unsigned int i = 0; i < nAgents; ++i) {

		bool collision = true;

		float xCoordinate;
		float yCoordinate;

		if (size(_obstacleList) == 0) {
			collision = false;
			xCoordinate = rand() % 400;
			yCoordinate = rand() % 400;
		}

		while (collision == true) {

			xCoordinate = rand() % 400;
			yCoordinate = rand() % 400;

			for (auto& obstacle : _obstacleList) {
				if (xCoordinate > obstacle[0]
					&& xCoordinate < obstacle[0] + obstacle[2]
					&& yCoordinate > obstacle[1]
					&& yCoordinate < obstacle[1] + obstacle[3])
					collision = true;
				else collision = false;
			}
		}

		Agent newAgent(xCoordinate, yCoordinate);
		_agents.push_back(newAgent);
	}
}

void World::addObject(float xOrigin, float yOrigin, float width, float height) {
	WorldObject object(xOrigin, yOrigin, width, height);
	_objects.push_back(object);

	// Doublecheck the following
	_obstacleList.push_back({ xOrigin - _agentDiameter, yOrigin - _agentDiameter,
		width + _agentDiameter, height + _agentDiameter });


}

void World::step(sf::RenderWindow& window) {
	for (auto& agent : _agents) {
		agent.step(_agents, _obstacleList);
		agent.draw(window);
	}
	
	for (auto& object : _objects) {
		object.draw(window);
	}
}
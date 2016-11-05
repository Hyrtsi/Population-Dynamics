#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics.hpp>
#include "agent.hpp"
#include "worldobject.hpp"
#include <vector>

class World {

public:
	std::vector<Agent> _agents;

	void addAgents(unsigned int nAgents);
	void addObject(float xOrigin, float yOrigin, float width, float height);
	void step(sf::RenderWindow& window);

	World(unsigned int nAgents);

private:
	float _agentDiameter = 20.0f;


	std::vector<std::vector<float>> _obstacleList;
	std::vector<WorldObject> _objects;
};
#endif
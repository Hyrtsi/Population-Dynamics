#ifndef AGENT_HPP
#define AGENT_HPP

#include <SFML/Graphics.hpp>
#include <vector>	// Needed?
#include <cstdint>	// Needed?
#include <time.h>	// Needed?





class Agent {
	enum state { wait, walk };
public:
	float _xPos;
	float _yPos;
	bool _isSick;
	float _health;

	Agent(float xPos, float yPos);

	void draw(sf::RenderWindow& window);
	void step(const std::vector<Agent>& agents,
		const std::vector<std::vector<float>>& obstacleList);
	void updateHealth(const std::vector<Agent>& agents);
	void move(const std::vector<Agent>& agents,
		const std::vector<std::vector<float>>& obstacleList);
	void setTarget(sf::Event& event);

private:
	float radius = 10.0f;
	float _dir;
	bool _hasTarget;
	float _xTarget;
	float _yTarget;

	bool _movingToTarget;

	state _state;

};






#endif

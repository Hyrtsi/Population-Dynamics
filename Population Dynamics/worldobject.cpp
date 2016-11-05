#include "stdafx.h"
#include "worldobject.hpp"
#include <vector>

WorldObject::WorldObject(float xOrigin, float yOrigin, float width, float height)
{
	_xOrigin = xOrigin;
	_yOrigin = yOrigin;
	_width = width;
	_height = height;
}


void WorldObject::draw(sf::RenderWindow& window) {
	sf::RectangleShape shape(sf::Vector2f(_width, _height));

	shape.setFillColor(sf::Color(100, 150, 120));

	shape.setPosition(_xOrigin, _yOrigin);
	window.draw(shape);
}


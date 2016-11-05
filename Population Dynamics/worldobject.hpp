#ifndef WORLDOBJECT_HPP
#define WORLDOBJECT_HPP

#include <SFML/Graphics.hpp>



class WorldObject {
	enum type { home, shop };
public:
	float _xOrigin;
	float _yOrigin;
	type _type;

	WorldObject(float xOrigin, float yOrigin, float width, float height);

	void draw(sf::RenderWindow& window);
	//void interact(void);

private:
	float _width;
	float _height;
};
#endif

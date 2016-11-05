// Population Dynamics.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "windows.h"
#include <iostream>
#include <vector>
#include <time.h>					// Random
#include <ctime>					// Random

#include "world.hpp"
#define WINDOWWIDTH 800
#define WINDOWHEIGHT 600


// Added properties:
//
// Stop chasing target when facing obstacles
// > smoother movement near obstacles


// Known problems:
//
// The agents get stuck when too close to each other
// 

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Hi?");

	unsigned int nAgents = 10;

	srand(time(NULL));

	World myworld(nAgents);

	myworld.addObject(100.0f, 250.0f, 350.0f, 50.0f);
	myworld.addAgents(nAgents);


	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		window.clear();

		myworld._agents[0].setTarget(event);
		myworld.step(window);

		Sleep(40);
		window.display();
	}

    return 0;
}


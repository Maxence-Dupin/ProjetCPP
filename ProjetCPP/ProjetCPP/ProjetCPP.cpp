// ProjetCPP.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <list>
#include "Sphere.hpp"
#include "Player.hpp"
#include "Wall.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Esquivate");
	window.setVerticalSyncEnabled(true);


	Player player;
	player.pos._x = 200;
	player.pos._y = 200;
	player.color = sf::Color::White;
	SetUpPlayer(player, 50.0f, 100.0f, 3, 10);
	player.circle.setPosition(200, 200);
	
	sf::Clock clock;

	//spheres manager
	std::vector<SphereEnnemy> ennemyList;

	for (int i = 0; i < 5; ++i) {
		float radius = static_cast <float> (rand() % (60 - 30 + 1) + 30);

		SphereEnnemy ennemy = SphereCreator(radius, 5.0f, sf::Color::Transparent, sf::Color::Red);

		SphereRenderer(ennemy);

		ennemyList.push_back(ennemy);
	}

	while (window.isOpen())
	{
		// Inputs
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			default:
				break;
			}
		}

		// Logique
		sf::Time elapsedTime = clock.restart(); //< Calcul du temps écoulé depuis la dernière boucle

		PlayerMouvement(player, elapsedTime.asSeconds());
		CollisionWithWall(player);

		for (SphereEnnemy oneEnnemy : ennemyList)
		{
			Collisions(oneEnnemy, player);
		}



		// Rendu
		window.clear();

		window.draw(player.circle);

		for (SphereEnnemy oneEnnemy : ennemyList) {
			window.draw(oneEnnemy.shape);
		}
		
		window.display();
	}
}
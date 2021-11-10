// ProjetCPP.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Sphere - Copie.hpp"
#include "Player.hpp"


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Esquivate");
	window.setVerticalSyncEnabled(true);

	Player player{};

	SetUpPlayer(player, 25, 100, 3, 10);

	std::cout << player.speed << std::endl;
	std::cout << player.pos._x << std::endl;
	std::cout << player.pos._y << std::endl;

	sf::Clock clock;

	//spheres manager
	std::vector<SphereEnnemy> ennemyList;

	for (int i = 0; i < 5; ++i) {
		float radius = rand() % (60 - 30 + 1) + 30;

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

		// Rendu
		window.clear();

		window.draw(player.circle);

		for (SphereEnnemy oneEnnemy : ennemyList) {
			window.draw(oneEnnemy.shape);
		}

		window.display();
	}
}

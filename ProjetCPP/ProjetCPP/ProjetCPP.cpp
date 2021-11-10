// ProjetCPP.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "PLayer.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Esquivate");
	window.setVerticalSyncEnabled(true);

	Player player{};

	SetUpPlayer(player, 25, 100, 3, 10);

	sf::CircleShape enemie;
	enemie.setRadius(50);
	enemie.setFillColor(sf::Color::Red);

	std::cout << player.speed << std::endl;
	std::cout << player.pos._x << std::endl;
	std::cout << player.pos._y << std::endl;

	sf::Clock clock;

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
		enemie.move(sf::Vector2f(0, 50 * elapsedTime.asSeconds()));

		PlayerMouvement(player, elapsedTime.asSeconds());

		// Rendu
		window.clear();

		window.draw(player.circle);
		window.draw(enemie);

		window.display();
	}
}


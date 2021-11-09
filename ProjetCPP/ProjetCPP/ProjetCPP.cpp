// ProjetCPP.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "EnemieManager.h"

void RectMovement(sf::RectangleShape& rect, float deltaTime);

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Ma première fenêtre");
	window.setVerticalSyncEnabled(true);

	sf::RectangleShape rect(sf::Vector2f(100, 100));
	rect.setPosition(sf::Vector2f(350.f, 250.f));

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

		RectMovement(rect, elapsedTime.asSeconds());

		Enemie test
		{
			0,
			sf::Color::Red,
			sf::Vector2f(0,0),
			pos
			{
				100,
				100,
			}
		};

		//SpawnAnEnemy(false, test);

		// Rendu
		window.clear();

		window.draw(rect);

		window.display();
	}
}

// Gestion des déplacement d'un rectangle
void RectMovement(sf::RectangleShape& rect, float deltaTime)
{
	float speed = 300.f; // 300 pixels par seconde

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		rect.move(sf::Vector2f(0.f, -speed * deltaTime));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		rect.move(sf::Vector2f(0.f, speed * deltaTime));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		rect.move(sf::Vector2f(-speed * deltaTime, 0.f));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		rect.move(sf::Vector2f(speed * deltaTime, 0.f));
}

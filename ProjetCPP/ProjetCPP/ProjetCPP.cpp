// ProjetCPP.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <SFML/Graphics.hpp>

void RectMovement(sf::RectangleShape& rect, float deltaTime);

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Esquivate");
	window.setVerticalSyncEnabled(true);

	sf::RectangleShape rect(sf::Vector2f(100, 100));
	rect.setPosition(sf::Vector2f(400.f, 300.f));

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

		// Rendu
		window.clear();

		window.draw(rect);

		window.display();
	}
}


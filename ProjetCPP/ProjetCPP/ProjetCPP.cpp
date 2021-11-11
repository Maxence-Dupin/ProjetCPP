// ProjetCPP.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Sphere.hpp"
#include "Player.hpp"

int main()
{
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(800, 600), "Esquivate");
	window.setVerticalSyncEnabled(true);


	Player player;
	player.pos._x = 400.0f;
	player.pos._y = 400.0f;
	player.color = sf::Color::White;
	SetUpPlayer(player, 50.0f, 300.0f, 3, 10);

	sf::Clock clock;

	//spheres manager
	std::vector<SphereEnnemy> ennemyList;

	for (int i = 0; i < 3; ++i) {
			float radius = static_cast <float> (rand() % (30 - 15 + 1) + 15);

			SphereEnnemy ennemy = SphereCreator(radius, 5.0f, sf::Color::Transparent, sf::Color::Red);

			SphereMovementDefinition(ennemy, player);

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


		auto it = ennemyList.begin();

		while (it != ennemyList.end()) {
			switch (it->movementType)
			{
			case MOVEMENT_TYPE::LINEAR: 
			case MOVEMENT_TYPE::LINEAR_TO_PLAYER:
				//mouvement linéaire orientation aléatoire ou vers le joueur
				SphereLinearMovement(*it, elapsedTime.asSeconds());
				break;
			case MOVEMENT_TYPE::ZIGZAG:
				//mouvement zigzag orientation aléatoire
				SphereZigZagMovement(*it, elapsedTime.asSeconds());
				break;
			case MOVEMENT_TYPE::DASH:
				//mouvement dash orientation aléatoire
				SphereDashMovement(*it, player, elapsedTime.asSeconds());
				break;
			default:
				break;
			}
			

			++it;
		}

		for (SphereEnnemy& oneEnnemy : ennemyList)
		{
			Collisions(oneEnnemy, player);
		}

		// Rendu
		window.clear();

		window.draw(player.circle);

		for (SphereEnnemy& oneEnnemy : ennemyList) {
			window.draw(oneEnnemy.shape);
		}

		window.display();
	}
}
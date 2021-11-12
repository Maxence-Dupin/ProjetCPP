// ProjetCPP.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Sphere.hpp"
#include "Player.hpp"
#include "WaveManagement.hpp"

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
	sf::Clock waveTimer;

	//wave manager
	WaveState gameWaveState;

	std::vector<SphereEnnemy> ennemyList;

	LoadNextWave(gameWaveState, ennemyList, player);

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
		sf::Time waveElapsedTime = waveTimer.getElapsedTime();

		sf::Time elapsedTime = clock.restart(); //< Calcul du temps écoulé depuis la dernière boucle

		PlayerMouvement(player, elapsedTime.asSeconds());

		//check if sprites are rendered and delete ennemy from vector if needed
		auto it = ennemyList.begin();
		while (it != ennemyList.end()) {
			sf::Vector2f currentPosition = it->shape.getPosition();
			bool canDelete = LeaveScreenManager(*it, currentPosition);

			if (canDelete)
			{
				it = ennemyList.erase(it);
			}
			else
			{
				++it;
			}
		}

		/*std::cout << waveElapsedTime.asSeconds() - gameWaveState.waveWaitTime << std::endl;*/
		
		//start between wave waiting time
		if (ennemyList.size() == 0 && gameWaveState.waveRunning) {
			waveElapsedTime = waveTimer.restart();
			gameWaveState.waveRunning = false;
			std::cout << "fin de vague" << std::endl;
			
		}
		//load next wave and start it
		else if ((waveElapsedTime.asSeconds() >= gameWaveState.waveWaitTime) && (gameWaveState.waveRunning == false))
		{
			if (gameWaveState.waveNumber % 2 == 0 && gameWaveState.bonusTime == false)
			{
				waveElapsedTime = waveTimer.restart();
				gameWaveState.bonusTime = true;
				std::cout << "bonus time!" << std::endl;

				//gameWaveState.waveRunning = LoadBonusWave(gameWaveState, availableBonusList, player);
			}
			else
			{
				waveElapsedTime = waveTimer.restart();
				std::cout << "debut de vague" << std::endl;

				gameWaveState.waveRunning = LoadNextWave(gameWaveState, ennemyList, player);
			}
		}

		


		//process all movements
		it = ennemyList.begin();

		while (it != ennemyList.end() && gameWaveState.waveRunning) {
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
			case MOVEMENT_TYPE::BREATHING:
				//mouvement dash orientation aléatoire
				SphereBreathingMovement(*it, elapsedTime.asSeconds());
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
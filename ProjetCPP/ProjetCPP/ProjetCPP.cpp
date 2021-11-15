// ProjetCPP.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include "Sphere.hpp"
#include "Player.hpp"
#include "Wall.h"
#include "WaveManagement.hpp"
#include "UI.hpp"

int main()
{
	srand(time(NULL));

	

	sf::RenderWindow window(sf::VideoMode(800, 600), "Esquivate");
	window.setVerticalSyncEnabled(true);


	Player player;
	player.pos._x = 400.0f;
	player.pos._y = 400.0f;
	player.color = sf::Color::White;
	SetUpPlayer(player, 25.0f, 300.0f);

	sf::Clock clock;
	sf::Clock waveTimer;


	// Initialisation des variables sf::Text pour l'UI
	sf::Font pixelated;
	pixelated.loadFromFile(getAssetsPathFromFolder() + "pixelated.ttf");
	sf::Text hpText;
	hpText.setPosition(20, 10);
	auto hpString = std::to_string(player.hp);
	hpText.setString(hpString + " HP");
	hpText.setFont(pixelated);
	sf::Text shieldText;
	shieldText.setPosition(650, 10);
	auto shieldString = std::to_string(player.shield);
	shieldText.setString("SHIELD : " + shieldString);
	shieldText.setFont(pixelated);
	sf::Text waveText;
	waveText.setPosition(320, 10);
	waveText.setString("WAVE 1");
	waveText.setFont(pixelated);



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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}

		// Logique
		if (player.hp <= 0) {
			window.close();
		}

		sf::Time waveElapsedTime = waveTimer.getElapsedTime();

		sf::Time elapsedTime = clock.restart(); //< Calcul du temps écoulé depuis la dernière boucle

		PlayerMouvement(player, elapsedTime.asSeconds());
		CollisionWithWall(player);


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
			if (gameWaveState.waveNumber % 5 == 0 && gameWaveState.bonusTime == false)
			{
				waveElapsedTime = waveTimer.restart();
				gameWaveState.bonusTime = true;
				std::cout << "bonus time!" << std::endl;
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
		UpdateHP(player, hpText);
		UpdateShield(player, shieldText);
		UpdateWave(gameWaveState.waveNumber, waveText);

		window.clear();

		window.draw(player.circle);

		for (SphereEnnemy& oneEnnemy : ennemyList) {
			window.draw(oneEnnemy.shape);
		}

		window.draw(hpText);
		window.draw(shieldText);
		window.draw(waveText);

		window.display();
	}
}

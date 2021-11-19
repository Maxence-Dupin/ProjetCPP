// ProjetCPP.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Sphere.hpp"
#include "Player.hpp"
#include "Wall.h"
#include "WaveManagement.hpp"
#include "BonusManager.hpp"
#include "BonusDrawer.hpp"
#include "UI.hpp"
#include "GameOver.hpp"

int main()
{
	srand(time(NULL));

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Esquivate", sf::Style::Default, settings);
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
	pixelated.loadFromFile(getAssetsPathFromRoot() + "pixelated.ttf");

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
	sf::Text gameOverText;
	gameOverText.setPosition(50, 400);
	gameOverText.setString("APPUYEZ  SUR  ESPACE  POUR  RECOMMENCER \n \n                           OU  ESCAPE  POUR  QUITTER");
	gameOverText.setFont(pixelated);
	gameOverText.setCharacterSize(40);
	sf::Text BonusText;
	BonusText.setPosition(60, 500);
	BonusText.setString("SELECTIONNEZ UN BONUS (U, I, O)");
	BonusText.setFont(pixelated);
	BonusText.setCharacterSize(50);

	//bonus cards letter
	std::vector<sf::Text> letters;

	sf::Text letterU, letterI, letterO;
	letterU.setString("U");
	letterI.setString("I");
	letterO.setString("0");

	letterU.setPosition(sf::Vector2f(220.f, 200.f));
	letterI.setPosition(sf::Vector2f(370.f, 200.f));
	letterO.setPosition(sf::Vector2f(520.f, 200.f));

	letters.push_back(letterU);
	letters.push_back(letterI);
	letters.push_back(letterO);

	for (sf::Text& oneLetter : letters)
	{
		oneLetter.setFont(pixelated);
		oneLetter.setCharacterSize(40);
		oneLetter.rotate(10);
	}

	

	//wave manager
	WaveState gameWaveState;

	std::vector<SphereEnnemy> ennemyList;
	std::map<int, POWER_UP> availablePowerUp;

	LoadNextWave(gameWaveState, ennemyList, player);

	std::map<int, sf::RectangleShape> bonusVisu;

	

	while (window.isOpen())
	{
		
		sf::Time waveElapsedTime = waveTimer.getElapsedTime();

		//std::cout << "bonusTime: " << gameWaveState.bonusTime << std::endl;
		// INPUTS
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				break;
			default:
				break;
			}
		}

		//close on ESCAPE
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}

		//restart with SPACE
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player.isAlive == false)
		{
			RestartGame(player, gameWaveState, ennemyList);
		}

		//bonus select with U, I, O
		if (gameWaveState.bonusTime)
		{
			gameWaveState.bonusTime = SelectBonus(availablePowerUp, player);

			if (!gameWaveState.bonusTime)
			{
				gameWaveState.waveNumber += 1;
			}
		}

		// LOGIQUE
		

		if (player.isAlive)
		{

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

			//start between wave waiting time
			if (ennemyList.size() == 0 && gameWaveState.waveRunning) {
				waveElapsedTime = waveTimer.restart();
				gameWaveState.waveRunning = false;
			}

			//load next wave and start it
			else if (waveElapsedTime.asSeconds() >= gameWaveState.waveWaitTime && gameWaveState.waveRunning == false)
			{

				if (gameWaveState.waveNumber % 2 == 0 && gameWaveState.waveNumber != 0 && !gameWaveState.bonusTime)
				{
					availablePowerUp = LoadBonusTime(enumSize);

					gameWaveState.bonusTime = true;

					waveElapsedTime = waveTimer.restart();
				}

				else if (!gameWaveState.bonusTime)
				{
					waveElapsedTime = waveTimer.restart();

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

			sf::Time time = player.clock.getElapsedTime();
			//std::cout << time.asMilliseconds() - player.lastHit << std:: endl;
			//changement de couleur du player si en phase d'invincibilité
			if (time.asMilliseconds() - player.lastHit + 300 < player.invincibleTime)
			{
				player.circle.setFillColor(sf::Color(255, 255, 255, 120));
			}
			else
			{
				player.circle.setFillColor(sf::Color::White);
			}
		}

		// Rendu
		UpdateHP(player, hpText);
		UpdateShield(player, shieldText);
		UpdateWave(gameWaveState.waveNumber, waveText);

		window.clear();

		if (player.isAlive)
		{
			if (!gameWaveState.bonusTime)
			{
				window.draw(player.circle);
			}
			
			//render ennemies
			for (SphereEnnemy& oneEnnemy : ennemyList) {
				window.draw(oneEnnemy.shape);
			}

			window.draw(hpText);
			window.draw(shieldText);
			window.draw(waveText);
			
			if (gameWaveState.bonusTime)
			{
				//affichage des lettres
				auto itLetterVector = letters.begin();
				int letterToDraw = 0;

				while (itLetterVector != letters.end())
				{
					window.draw(letters[letterToDraw]);

					++letterToDraw;
					++itLetterVector;
				}
				
				//affichage du texte choix bonus
				window.draw(BonusText);

				//affichage des 3 bonus possibles
				auto itPowerUpMap = availablePowerUp.begin();
				int bonusDrew = 0;

				while (itPowerUpMap != availablePowerUp.end())
				{
					switch (bonusDrew)
					{
					case 0:
						DrawBonus(window, 250.f, 300.f, itPowerUpMap->second);
						break;
					case 1:
						DrawBonus(window, 400.f, 300.f, itPowerUpMap->second);
						break;
					case 2:
						DrawBonus(window, 550.f, 300.f, itPowerUpMap->second);
						break;
					default:
						break;
					}

					++bonusDrew;
					++itPowerUpMap;
				}
			}
		}
		else
		{
			window.draw(gameOverText);
		}

		window.display();
	}
}

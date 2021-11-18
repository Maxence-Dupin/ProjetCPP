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
	SetUpPlayer(player, 25.0f, 300.0f, 3, 10);

	sf::Clock clock;
	sf::Clock waveTimer;

	//wave manager
	WaveState gameWaveState;

	std::vector<SphereEnnemy> ennemyList;

	LoadNextWave(gameWaveState, ennemyList, player);

	std::map<int, sf::RectangleShape> bonusVisu;
	bool hasChooseBonus = true;
	bool hasDrawBonus = false;

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
			case sf::Event::MouseButtonPressed:
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					while (hasChooseBonus == false)
					{
						sf::Vector2f clickPos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
						hasChooseBonus = buttonPressed(clickPos, bonusVisu, player);
					}
					bonusVisu.clear();
				}
			default:
				break;
			}
		}

		// Logique
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

			if ((gameWaveState.waveNumber % 2 == 0) && (gameWaveState.bonusTime) && !hasDrawBonus)
			{
				std::map<int, POWER_UP> currentBonus = LoadBonusTime(enumSize);
				bonusVisu = setUpBonusVisu(currentBonus);
				hasDrawBonus = true;
				hasChooseBonus = false;
					
				gameWaveState.bonusTime == false;

				waveElapsedTime = waveTimer.restart();
				std::cout << "bonus time!" << std::endl;
			}
			else if (hasChooseBonus)
			{
				waveElapsedTime = waveTimer.restart();
				std::cout << "debut de vague" << std::endl;

				hasDrawBonus = false;

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

		for (int i = 0; i < bonusVisu.size(); i++)
		{
			window.draw(bonusVisu[i]);
		}		

		//affichage structure visuelle d'un bonus
		BonusVisual visualToDraw = ShieldUpDraw(200.f, 300.f);

		window.draw(visualToDraw.bonusFrame);
		window.draw(visualToDraw.bonusCircle);

		for (sf::ConvexShape oneComponent : visualToDraw.bonusShape) {
			window.draw(oneComponent);
		}

		window.display();
	}
}

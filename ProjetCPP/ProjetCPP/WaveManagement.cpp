#include <iostream>;
#include <SFML/Graphics.hpp>;
#include "Sphere.hpp";
#include "Player.hpp";
#include "WaveManagement.hpp";

bool LoadNextWave(WaveState& waveState, std::vector<SphereEnnemy>& ennemyList, Player& player)
{
	for (int i = 0; i < waveState.ennemyNumber; ++i) {
		float radius = static_cast <float> (rand() % (30 - 15 + 1) + 15);

		SphereEnnemy ennemy = SphereCreator(radius, 5.0f, sf::Color::Transparent, sf::Color::Red);

		SphereMovementDefinition(ennemy, player);

		SphereRenderer(ennemy);

		ennemyList.push_back(ennemy);
	}

	waveState.waveNumber += 1;

	if (waveState.ennemyNumber < 15)
	{
		waveState.ennemyNumber += 2;
	}
	
	
	return true;
}
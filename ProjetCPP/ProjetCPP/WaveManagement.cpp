#include "WaveManagement.hpp";

bool LoadNextWave(WaveState& waveState, std::vector<SphereEnnemy>& ennemyList, Player& player)
{
	waveState.waveNumber += 1;
	std::cout << "vague " << waveState.waveNumber << std::endl;

	for (int i = 0; i < waveState.ennemyNumber; ++i) {
		float radius = static_cast <float> (rand() % (30 - 15 + 1) + 15);

		SphereEnnemy ennemy = SphereCreator(radius, 5.0f, sf::Color::Transparent, sf::Color::Red);

		SphereMovementDefinition(ennemy, player);

		SphereRenderer(ennemy);

		ennemyList.push_back(ennemy);
	}


	if (waveState.ennemyNumber < 15)
	{
		waveState.ennemyNumber += 2;
	}

	return true;
}
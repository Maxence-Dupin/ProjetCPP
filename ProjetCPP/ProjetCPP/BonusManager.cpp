#include <iostream>;
#include <SFML/Graphics.hpp>;
#include <map>;
#include "Player.hpp";
#include "BonusManager.hpp";

void LoadBonusTime(int enumSize)
{
	std::map<int, POWER_UP> availablePowerUps;

	for (int i = 0; i < 3; i++)
	{
		auto it = availablePowerUps.begin();

		int randomNumber = rand() % enumSize;
		it = availablePowerUps.find(randomNumber);

		while (it != availablePowerUps.end()) {
			randomNumber = rand() % enumSize;
			it = availablePowerUps.find(randomNumber);
		}

		availablePowerUps[randomNumber] = (POWER_UP)randomNumber;
	}

	auto itg = availablePowerUps.begin();

	while (itg != availablePowerUps.end())
	{
		std::cout << itg->first << " : " << itg->second << std::endl;
		itg++;
	}
}
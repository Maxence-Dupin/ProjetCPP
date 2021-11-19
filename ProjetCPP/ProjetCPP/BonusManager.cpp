#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>
#include "Player.hpp"
#include "BonusManager.hpp"

std::map<int, POWER_UP> LoadBonusTime(int enumSize)//choose 3 powerup
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
		std::cout << "choix num : " << itg->first << " : " << "bonnus num : " << itg->second << std::endl;
		itg++;
	}

	return availablePowerUps;

}


void SizeDown(Player& player)
{
	std::cout << player.radius << " --> ";
	player.radius -= (player.radius * 15) / 100;
	player.circle.setRadius(player.radius);
	std::cout << player.radius;
}

void SpeedBonus(Player& player)
{
	std::cout << player.speed << " --> ";
	player.speed += 50;
	std::cout << player.speed;
}

void LifeUp (Player& player)
{
	player.hp += 1;
}
void ShieldUp(Player& player)
{
	player.maxShield += 5;
}

void applyBonus(std::map<int, sf::RectangleShape> bonusVisu, int number, Player& player)
{
	if (bonusVisu[number].getOutlineColor() == sf::Color::Green)
	{
		SizeDown(player);
		std::cout << "Size Down Player";
	}
	if (bonusVisu[number].getOutlineColor() == sf::Color::Yellow)
	{
		SpeedBonus(player);
		std::cout << "Speed UP";
	}
	if (bonusVisu[number].getOutlineColor() == sf::Color::Red)
	{
		LifeUp(player);
		std::cout << "Life++";
	}
	if (bonusVisu[number].getOutlineColor() == sf::Color::Blue)
	{
		ShieldUp(player);
		std::cout << "Shield ++";
	}
}


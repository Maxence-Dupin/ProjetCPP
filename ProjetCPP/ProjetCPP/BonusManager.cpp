#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>
#include "Player.hpp"
#include "WaveManagement.hpp"
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
	if (player.radius <= 18.f)
	{
		player.radius -= (player.radius * 15) / 100;
		player.circle.setRadius(player.radius);
	}
}

void SpeedBonus(Player& player)
{
	if (player.speed <= 400.f)
		player.speed += 50.f;
}

void LifeUp (Player& player)
{
	if (player.hp < 3)
		player.hp += 1;
}
void ShieldUp(Player& player)
{	
	if (player.shield < 3)
		player.shield = 3;
}

void ApplyBonus(int number, Player& player)
{
	switch (number)
	{
	case POWER_UP::LIFE_UP:
		LifeUp(player);
		break;
	case POWER_UP::SHIELD_UP:
		ShieldUp(player);
		break;
	case POWER_UP::SIZE_DOWN:
		SizeDown(player);
		break;
	case POWER_UP::SPEED_UP:
		SpeedBonus(player);
		break;
	default:
		break;
	}
}

bool SelectBonus(std::map<int, POWER_UP> availablePowerUp, Player& player) 
{
	auto it = availablePowerUp.begin();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))//bonus left
	{
		ApplyBonus(it->second, player);

		return false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))//bonus center
	{
		for(int i = 0; i < 1; i++)
			it++;

		if(it != availablePowerUp.end())
			ApplyBonus(it->second, player);

		return false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))//bonus right
	{
		for (int i = 0; i < 2; i++)
			it++;

		if (it != availablePowerUp.end())
			ApplyBonus(it->second, player);

		return false;
	}
	else
		return true;
}


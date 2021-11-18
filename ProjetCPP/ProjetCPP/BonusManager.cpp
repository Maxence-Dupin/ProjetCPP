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
		std::cout << "choix num : " << itg->first << " : " << "bonnus num" << itg->second << std::endl;
		itg++;
	}

	return availablePowerUps;

}

sf::Color ChooseColor(std::map<int, POWER_UP> currentBonus, int number)
{
	if (currentBonus[number] == 0)
	{
		return sf::Color::Green;
	}
	if (currentBonus[number] == 1)
	{
		return sf::Color::Yellow;
	}
	if (currentBonus[number] == 2)
	{
		return sf::Color::Red;
	}
	if (currentBonus[number] == 3)
	{
		return sf::Color::Blue;
	}
}

std::map<int, sf::RectangleShape> setUpBonusVisu(std::map<int, POWER_UP> currentBonus)
{
	std::map<int, sf::RectangleShape> bonusVisu;

	sf::RectangleShape Bonus1;
	Bonus1.setSize(sf::Vector2f(80, 100));
	Bonus1.setPosition(sf::Vector2f(200, 150));
	Bonus1.setFillColor(ChooseColor(currentBonus, 0));
	bonusVisu[0] = Bonus1;

	sf::RectangleShape Bonus2;
	Bonus2.setSize(sf::Vector2f(80, 100));
	Bonus2.setPosition(sf::Vector2f(300, 150));
	Bonus2.setFillColor(ChooseColor(currentBonus, 1));
	bonusVisu[1] = Bonus2;

	sf::RectangleShape Bonus3;
	Bonus3.setSize(sf::Vector2f(80, 100));
	Bonus3.setPosition(sf::Vector2f(400, 150));
	Bonus3.setFillColor(ChooseColor(currentBonus, 2));
	bonusVisu[2] = Bonus3;

	return bonusVisu;
}


void SizeDown(Player& player)
{
	std::cout << player.radius;
	player.radius -= 5;
	std::cout << player.radius;
}

void SpeedBonus(Player& player)
{
	std::cout << player.speed;
	player.speed += 20;
	std::cout << player.speed;
}

void LifeUp (Player& player)
{
	player.hp += 1;
}
void ShieldUp(Player& player)
{
	player.shield += 5;
}

void applyBonus(std::map<int, sf::RectangleShape> bonusVisu, int number, Player& player)
{
	if (bonusVisu[number].getFillColor() == sf::Color::Green)
	{
		SizeDown(player);
		std::cout << "Size Down Player";
	}
	if (bonusVisu[number].getFillColor() == sf::Color::Yellow)
	{
		SpeedBonus(player);
		std::cout << "Speed UP";
	}
	if (bonusVisu[number].getFillColor() == sf::Color::Red)
	{
		LifeUp(player);
		std::cout << "Life++";
	}
	if (bonusVisu[number].getFillColor() == sf::Color::Blue)
	{
		ShieldUp(player);
		std::cout << "Shield ++";
	}
}

bool buttonPressed (sf::Vector2f clickPos, std::map<int, sf::RectangleShape> bonusVisu, Player& player)
{
	if ((clickPos.x >= bonusVisu[0].getPosition().x && clickPos.x <= bonusVisu[0].getPosition().x + bonusVisu[0].getSize().x) && (clickPos.y >= bonusVisu[0].getPosition().y && clickPos.y <= bonusVisu[0].getPosition().y + bonusVisu[0].getSize().y))//button1
	{
		applyBonus(bonusVisu, 0, player);
		std::cout << "Bonus 1";
		return true;
	}

	if ((clickPos.x >= bonusVisu[1].getPosition().x && clickPos.x <= bonusVisu[1].getPosition().x + bonusVisu[1].getSize().x) && (clickPos.y >= bonusVisu[1].getPosition().y && clickPos.y <= bonusVisu[1].getPosition().y + bonusVisu[1].getSize().y))//button2
	{
		applyBonus(bonusVisu, 1, player);

		std::cout << "Bonus 2";
		return true;
	}

	if ((clickPos.x >= bonusVisu[2].getPosition().x && clickPos.x <= bonusVisu[2].getPosition().x + bonusVisu[2].getSize().x) && (clickPos.y >= bonusVisu[2].getPosition().y && clickPos.y <= bonusVisu[2].getPosition().y + bonusVisu[2].getSize().y))
	{
		applyBonus(bonusVisu, 2, player);

		std::cout << "Bonus 3";
		return true;
	}
}


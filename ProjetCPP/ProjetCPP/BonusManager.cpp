#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>
#include "Player.hpp"
#include "BonusManager.hpp"

std::map<int, POWER_UP> LoadBonusTime(int enumSize)//choose 3 powerup
{
	std::map<int, POWER_UP> availablePowerUps;
	int lastBonus[3]{5,6,7};

	for (int i = 0; i < 3; i++)
	{
		auto it = availablePowerUps.begin();

		int randomNumber = rand() % enumSize;
		it = availablePowerUps.find(randomNumber);

		while (it != availablePowerUps.end()) {
			randomNumber = rand() % enumSize;
			it = availablePowerUps.find(randomNumber);
		}

		if (randomNumber != lastBonus[0] && randomNumber != lastBonus [1])
		{
			availablePowerUps[i] = (POWER_UP)randomNumber;
			lastBonus[i] = randomNumber;
			std::cout << "Add BONUS" << std::endl;
			for (int j = 0; j < i; j++)
			{
				std::cout << lastBonus[j] << " ";
			}
		}
		else
		{
			i--;
			int randomNumber = rand() % enumSize;
			std::cout << randomNumber;
			for (int j = 0; j < i; j++)
			{
				std::cout << lastBonus[j] << " ";
				std::cout << std::endl;

			}
		}
	}

	auto itg = availablePowerUps.begin();

	while (itg != availablePowerUps.end())
	{
		std::cout << "choix num : " << itg->first << " : " << "bonnus num : " << itg->second << std::endl;
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
	Bonus1.setSize(sf::Vector2f(100, 60));
	Bonus1.setPosition(sf::Vector2f(150, 270));
	Bonus1.setOutlineThickness(15);
	Bonus1.setOutlineColor(ChooseColor(currentBonus, 0));
	Bonus1.setFillColor(sf::Color::Transparent);
	bonusVisu[0] = Bonus1;

	sf::RectangleShape Bonus2;
	Bonus2.setSize(sf::Vector2f(100, 60));
	Bonus2.setPosition(sf::Vector2f(350, 270));
	Bonus2.setOutlineThickness(15);
	Bonus2.setOutlineColor(ChooseColor(currentBonus, 1));
	Bonus2.setFillColor(sf::Color::Transparent);
	bonusVisu[1] = Bonus2;

	sf::RectangleShape Bonus3;
	Bonus3.setSize(sf::Vector2f(100, 60));
	Bonus3.setPosition(sf::Vector2f(550, 270));
	Bonus3.setOutlineThickness(15);
	Bonus3.setOutlineColor(ChooseColor(currentBonus, 2));
	Bonus3.setFillColor(sf::Color::Transparent);
	bonusVisu[2] = Bonus3;

	return bonusVisu;
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
	player.shield += 5;
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

bool buttonPressed (sf::Vector2f clickPos, std::map<int, sf::RectangleShape> bonusVisu, Player& player)
{
	if ((clickPos.x >= bonusVisu[0].getPosition().x && clickPos.x <= bonusVisu[0].getPosition().x + bonusVisu[0].getSize().x) && (clickPos.y >= bonusVisu[0].getPosition().y && clickPos.y <= bonusVisu[0].getPosition().y + bonusVisu[0].getSize().y))//button1
	{
		applyBonus(bonusVisu, 0, player);
		std::cout << "Bonus 1";
		return true;
	}

	else if ((clickPos.x >= bonusVisu[1].getPosition().x && clickPos.x <= bonusVisu[1].getPosition().x + bonusVisu[1].getSize().x) && (clickPos.y >= bonusVisu[1].getPosition().y && clickPos.y <= bonusVisu[1].getPosition().y + bonusVisu[1].getSize().y))//button2
	{
		applyBonus(bonusVisu, 1, player);

		std::cout << "Bonus 2";
		return true;
	}

	else if ((clickPos.x >= bonusVisu[2].getPosition().x && clickPos.x <= bonusVisu[2].getPosition().x + bonusVisu[2].getSize().x) && (clickPos.y >= bonusVisu[2].getPosition().y && clickPos.y <= bonusVisu[2].getPosition().y + bonusVisu[2].getSize().y))
	{
		applyBonus(bonusVisu, 2, player);

		std::cout << "Bonus 3";
		return true;
	}
}


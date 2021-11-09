#include <iostream>
#include <SFML/Graphics.hpp>

struct pos
{
	float _x;
	float _y;
};

struct Enemie
{
	int number;
	sf::Color color;
	sf::Vector2f patern;
	pos pos;
};

std::map<int, Enemie> CreateEnemie(int numberOfWaves, std::map<int, Enemie>& allEnemies)
{
	for(int i; i < numberOfWaves; i++)
	{
		
		allEnemies[i] = {i,sf::Color::Red,sf::Vector2f(),pos{0,-300}};
	}
}

void SpawnAnEnemy(bool& nextWaves, Enemie& enemie)
{
	if (nextWaves)
	{
		nextWaves = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		sf::RectangleShape rec(sf::Vector2f(enemie.pos._x, enemie.pos._y));

		std::cout << "Number : " << enemie.number << " / " << "Pos x/Y : " << enemie.pos._x << "/" << enemie.pos._y;
	}
}
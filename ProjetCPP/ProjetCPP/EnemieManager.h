#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>


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

void SpawnAnEnemy(bool nextWaves, Enemie& enemie);

std::map<int, Enemie> enemieList;

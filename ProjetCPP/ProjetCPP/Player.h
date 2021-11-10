#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>


struct pos
{
	float _x;
	float _y;
};


struct Player
{
	sf::CircleShape circle;
	sf::Color color;

	pos pos;

	float speed;
	int hp;
	int shield;
};

void SetUpPlayer(Player& player, int radius, float speed, int hp, int shield);

void PlayerMouvement(Player& player, float deltaTime);

void ChangeLife(Player& player, int amout);

void ChangeShield(Player& player, int amout);


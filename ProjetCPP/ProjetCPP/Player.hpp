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
	sf::Clock clock;

	pos pos;

	float speed;
	float radius;
	int hp;
	int maxHp = 3;
	int shield;
	int maxShield = 3;
	bool isInvincible = true;
	float lastHit = 0.0f;
	float newHit;
	float invincibleTime = 500.0f;
	bool isAlive = false;
};

void PlayerMouvement(Player& player, float deltaTime);
void ChangeLife(Player& player, int amout);
void ChangeShield(Player& player, int amout);
void SetUpPlayer(Player& player, float radius, float speed);
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.hpp"

void SetUpPlayer(Player& player, float radius, float speed, int hp, int shield)
{
	player.speed = speed;
	player.hp = hp;
	player.shield = shield;
	player.radius = radius;
	player.circle.setPosition(sf::Vector2f(player.pos._x, player.pos._y));
	player.circle.setRadius(player.radius);
	player.circle.setFillColor(player.color);
}


// Gestion des déplacement d'un rectangle
void PlayerMouvement(Player& player, float deltaTime)
{
	float speed = player.speed; // 300 pixels par seconde

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))//up
	{
		player.circle.move(sf::Vector2f(0.f, -speed * deltaTime));
		player.pos._y -= speed * deltaTime;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))//down
	{
		player.circle.move(sf::Vector2f(0.f, speed * deltaTime));
		player.pos._y += speed * deltaTime;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))//right
	{
		player.circle.move(sf::Vector2f(-speed * deltaTime, 0.f));
		player.pos._x -= speed * deltaTime;

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))//left
	{
		player.circle.move(sf::Vector2f(speed * deltaTime, 0.f));
		player.pos._x += speed * deltaTime;

	}
}

void ChangeLife(Player& player, int amout)
{
	player.hp += amout;
}

void ChangeShield(Player& player, int amout)
{
	player.shield += amout;
}


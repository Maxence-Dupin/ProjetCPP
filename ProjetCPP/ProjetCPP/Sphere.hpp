#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include "Player.hpp"

struct EnnemyPosition
{
	float posX;
	float posY;
};

struct SphereEnnemy
{
	sf::CircleShape shape;
	float radius;
	float outlineThickness;
	EnnemyPosition position;
	sf::Color fillColor;
	sf::Color borderColor;
	sf::Vector2f direction;
	float dist;
};

SphereEnnemy SphereCreator(float radius, float outlineThickness, sf::Color fillColor, sf::Color borderColor);

void SphereRenderer(SphereEnnemy& ennemy);

void SphereMovement(SphereEnnemy& ennemy, float deltaTime);

sf::Vector2f Lerp(sf::Vector2f from, sf::Vector2f to, float t);

float normalized(sf::Vector2f vector);

void Collisions(SphereEnnemy& ennemy, Player& player);


#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>

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
};

SphereEnnemy SphereCreator(float radius, float outlineThickness, sf::Color fillColor, sf::Color borderColor);
void SphereRenderer(SphereEnnemy& ennemy);
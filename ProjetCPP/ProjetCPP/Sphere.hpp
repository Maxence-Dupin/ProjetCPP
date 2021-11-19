#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include "Player.hpp"

enum MOVEMENT_TYPE {
	LINEAR,
	LINEAR_TO_PLAYER,
	ZIGZAG,
	DASH,
	BREATHING,
};

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
	float compteur = 0.0f;
	int changeLeft = 4;
	bool hasBeenRendered = false;
	MOVEMENT_TYPE movementType; 
};

SphereEnnemy SphereCreator(float radius, float outlineThickness, sf::Color fillColor, sf::Color borderColor);

void SphereMovementDefinition(SphereEnnemy& ennemy, Player& player);

void SphereRenderer(SphereEnnemy& ennemy);

void SphereLinearMovement(SphereEnnemy& ennemy, float deltaTime);

void SphereZigZagMovement(SphereEnnemy& ennemy, float deltaTime);

void SphereDashMovement(SphereEnnemy& ennemy, Player& player, float deltaTime);

void SphereBreathingMovement(SphereEnnemy& ennemy, float deltaTime);

bool LeaveScreenManager(SphereEnnemy& ennemy, sf::Vector2f currentPosition);

float vecNorme(sf::Vector2f vector);

void Collisions(SphereEnnemy& ennemy, Player& player);


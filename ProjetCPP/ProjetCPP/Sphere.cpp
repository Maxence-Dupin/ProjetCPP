#include<iostream>;
#include<SFML/Graphics.hpp>;
#include "Sphere.hpp"

SphereEnnemy SphereCreator(float radius, float outlineThickness, sf::Color fillColor, sf::Color borderColor) {
	EnnemyPosition position;
	SphereEnnemy ennemy;

	sf::CircleShape ennemyShape;

	if (rand() % 2) {
		position.posX = rand() % (0 - (-50) + 1) + 0;
	}
	else {
		position.posX = rand() % (850 - 800 + 1) + 800;
	}

	if (rand() % 2) {
		position.posY = rand() % (0 - (-50) + 1) + 0;
	}
	else {
		position.posY = rand() % (650 - 600 + 1) + 600;
	}


	ennemy.position = position;

	ennemy.shape.setOrigin(ennemy.position.posX, ennemy.position.posY);

	ennemy.shape = ennemyShape;
	ennemy.radius = radius;
	ennemy.outlineThickness = outlineThickness;
	ennemy.fillColor = fillColor;
	ennemy.borderColor = borderColor;

	ennemy.direction = sf::Vector2f(rand() % (700 - 100 + 1) + 100, rand() % (500 - 100 + 1) + 100);

	return ennemy;
}

void SphereRenderer(SphereEnnemy& ennemy) {
	ennemy.shape.setPosition(sf::Vector2f(ennemy.position.posX, ennemy.position.posY));
	ennemy.shape.setRadius(ennemy.radius);
	ennemy.shape.setOutlineThickness(ennemy.outlineThickness);
	ennemy.shape.setFillColor(ennemy.fillColor);
	ennemy.shape.setOutlineColor(ennemy.borderColor);
}

void SphereMovement(SphereEnnemy& ennemy, float deltaTime) {
	float directionX = ennemy.direction.x - ennemy.position.posX;
	float directionY = ennemy.direction.y - ennemy.position.posY;

	int dist = normalized(sf::Vector2f(directionX * deltaTime, directionY * deltaTime));

	ennemy.shape.move(sf::Vector2f(directionX * deltaTime * 3 / dist, directionY * deltaTime * 3 / dist));
}

int normalized(sf::Vector2f vector) {
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}

sf::Vector2f Lerp(sf::Vector2f from, sf::Vector2f to, float t)
{
	return from + (to - from) * t;
}
void Collisions(SphereEnnemy& ennemy, Player& player)
{
	float dx = ennemy.position.posX - player.pos._x + ennemy.radius - player.radius;
	float dy = ennemy.position.posY - player.pos._y + ennemy.radius - player.radius;
	float distance = sqrt(dx * dx + dy * dy);

	if (distance < ennemy.radius + ennemy.outlineThickness + player.radius)
	{
		std::cout << "collision !" << std::endl;
		if (player.shield <= 0)
		{
			player.shield = 0;
			ChangeLife(player, -1);
			std::cout << player.hp << std::endl;
		}
		else
		{
			ChangeShield(player, -1);
			std::cout << player.shield << std::endl;
		}
	}
}

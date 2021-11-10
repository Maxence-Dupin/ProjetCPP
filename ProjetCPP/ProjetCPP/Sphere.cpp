#include<iostream>;
#include<SFML/Graphics.hpp>;
#include "Sphere.hpp"

SphereEnnemy SphereCreator(float radius, float outlineThickness, sf::Color fillColor, sf::Color borderColor) {
	EnnemyPosition position;
	SphereEnnemy ennemy;

	sf::CircleShape ennemyShape;

	position.posX = rand() % (750 - 50 + 1) + 50;
	position.posY = rand() % (550 - 50 + 1) + 50;

	ennemy.position = position;

	ennemy.shape.setOrigin(ennemy.position.posX, ennemy.position.posY);
	
	ennemy.shape = ennemyShape;
	ennemy.radius = radius;
	ennemy.outlineThickness = outlineThickness;
	ennemy.fillColor = fillColor;
	ennemy.borderColor = borderColor;

	return ennemy;
}

void SphereRenderer(SphereEnnemy& ennemy) {
	ennemy.shape.setPosition(sf::Vector2f(ennemy.position.posX, ennemy.position.posY));
	ennemy.shape.setRadius(ennemy.radius);
	ennemy.shape.setOutlineThickness(ennemy.outlineThickness);
	ennemy.shape.setFillColor(ennemy.fillColor);
	ennemy.shape.setOutlineColor(ennemy.borderColor);
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
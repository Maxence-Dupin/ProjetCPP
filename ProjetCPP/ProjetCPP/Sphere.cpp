#include <iostream>;
#include <SFML/Graphics.hpp>;
#include "Sphere.hpp"

SphereEnnemy SphereCreator(float radius, float outlineThickness, sf::Color fillColor, sf::Color borderColor) {
	EnnemyPosition position;
	SphereEnnemy ennemy;

	sf::CircleShape ennemyShape;

	//d�finition position de d�part
	position.posX = rand() % (900 - (-100) + 1) - 100;
	position.posY = rand() % (700 - (-100) + 1) - 100;

	while (position.posX > 0 && position.posX < 800) {
		position.posX = rand() % (900 - (-100) + 1) - 100;
	}

	while (position.posY > 0 && position.posX < 600) {
		position.posY = rand() % (700 - (-100) + 1) - 100;
	}

	//std::cout << position.posX << " : " << position.posY << std::endl;

	ennemy.position = position;

	ennemy.shape.setOrigin(ennemy.position.posX, ennemy.position.posY);

	ennemy.shape = ennemyShape;
	ennemy.radius = radius;
	ennemy.outlineThickness = outlineThickness;
	ennemy.fillColor = fillColor;
	ennemy.borderColor = borderColor;

	//d�finition type de mouvement
	int randomNumber = rand() % 5 + 1;

	switch (randomNumber)
	{
	case 1:
		ennemy.movementType = MOVEMENT_TYPE::LINEAR;
		ennemy.borderColor = sf::Color::Blue;
		break;
	case 2:
		ennemy.movementType = MOVEMENT_TYPE::LINEAR_TO_PLAYER;
		ennemy.borderColor = sf::Color::Green;
		break;
	case 3:
		ennemy.movementType = MOVEMENT_TYPE::ZIGZAG;
		ennemy.borderColor = sf::Color::Yellow;
		break;
	case 4:
		ennemy.movementType = MOVEMENT_TYPE::DASH;
		ennemy.borderColor = sf::Color::Red;
		break;
	case 5:
		ennemy.movementType = MOVEMENT_TYPE::BREATHING;
		ennemy.borderColor = sf::Color::White;
		break;
	default:
		break;
	}

	return ennemy;
}

void SphereMovementDefinition(SphereEnnemy& ennemy, Player& player) {
	//d�finition de la direction
	sf::Vector2f targetPoint;

	switch (ennemy.movementType)
	{
	case MOVEMENT_TYPE::LINEAR:
	case MOVEMENT_TYPE::ZIGZAG:
	case MOVEMENT_TYPE::BREATHING:
		targetPoint = sf::Vector2f(rand() % (700 - 100 + 1) + 100, rand() % (500 - 100 + 1) + 100);
		break;
	case MOVEMENT_TYPE::LINEAR_TO_PLAYER:
	case MOVEMENT_TYPE::DASH:
		targetPoint = player.circle.getPosition();
		break;
	default:
		break;
	}

	float norme = vecNorme(sf::Vector2f(targetPoint.x - ennemy.position.posX, targetPoint.y - ennemy.position.posY));

	ennemy.direction = sf::Vector2f((targetPoint.x - ennemy.position.posX) / norme, (targetPoint.y - ennemy.position.posY) / norme);
}

void SphereRenderer(SphereEnnemy& ennemy) {
	ennemy.shape.setPosition(sf::Vector2f(ennemy.position.posX, ennemy.position.posY));
	ennemy.shape.setRadius(ennemy.radius);
	ennemy.shape.setOutlineThickness(ennemy.outlineThickness);
	ennemy.shape.setFillColor(ennemy.fillColor);
	ennemy.shape.setOutlineColor(ennemy.borderColor);
}

void SphereLinearMovement(SphereEnnemy& ennemy, float deltaTime) {
	float speed = 300.f;

	ennemy.shape.move(sf::Vector2f(ennemy.direction.x  * speed * deltaTime, ennemy.direction.y * speed * deltaTime ));

	ennemy.position.posX += ennemy.direction.x * speed * deltaTime;
	ennemy.position.posY += ennemy.direction.y * speed * deltaTime;
}

void SphereZigZagMovement(SphereEnnemy& ennemy, float deltaTime) {
	float speed = 200.f;

	if (ennemy.compteur < 40)
	{
		ennemy.shape.move(sf::Vector2f(ennemy.direction.x * speed * deltaTime, ennemy.direction.y * speed * deltaTime));
		++ennemy.compteur;

		ennemy.position.posX += ennemy.direction.x * speed * deltaTime;
		ennemy.position.posY += ennemy.direction.y * speed * deltaTime;
	}
	else if (ennemy.compteur < 80)
	{
		++ennemy.compteur;
		ennemy.shape.move(sf::Vector2f(- ennemy.direction.x * speed * deltaTime, ennemy.direction.y * speed * deltaTime));

		ennemy.position.posX -= ennemy.direction.x * speed * deltaTime;
		ennemy.position.posY += ennemy.direction.y * speed * deltaTime;
	}
	else
	{
		ennemy.compteur = 0;
	}
}

void SphereDashMovement(SphereEnnemy& ennemy, Player& player, float deltaTime) {
	float speed = 200.f;

	if (ennemy.changeLeft == 0)
	{
		ennemy.borderColor = sf::Color::Green;
		ennemy.shape.setOutlineColor(ennemy.borderColor);
	}

	//changement vitesse pour le dash
	if (ennemy.compteur >= 0 && ennemy.compteur <= 10) 
	{
		speed = 400.f;
	}
	else
	{
		speed = 200.f;
	}

	//change de direction vers le player
	if (ennemy.compteur >= 80 && ennemy.changeLeft > 0)
	{
		ennemy.compteur = 0;
		ennemy.changeLeft--;
		sf::Vector2f targetPoint = player.circle.getPosition();

		float norme = vecNorme(sf::Vector2f(targetPoint.x - ennemy.position.posX, targetPoint.y - ennemy.position.posY));

		ennemy.direction = sf::Vector2f((targetPoint.x - ennemy.position.posX) / norme, (targetPoint.y - ennemy.position.posY) / norme);
	}
	//garde sa trajectoire
	else 
	{
		++ennemy.compteur;
		ennemy.shape.move(sf::Vector2f(ennemy.direction.x * speed * deltaTime, ennemy.direction.y * speed * deltaTime));

		ennemy.position.posX += ennemy.direction.x * speed * deltaTime;
		ennemy.position.posY += ennemy.direction.y * speed * deltaTime;
	}

}

void SphereBreathingMovement(SphereEnnemy& ennemy, float deltaTime) {
	float speed = 100.f;

	ennemy.compteur += 0.02f;
	ennemy.shape.move(sf::Vector2f(ennemy.direction.x * speed * deltaTime, ennemy.direction.y * speed * deltaTime));

	ennemy.shape.setRadius(ennemy.shape.getRadius() + 0.5 * cosf(ennemy.compteur));

	ennemy.position.posX += ennemy.direction.x * speed * deltaTime;
	ennemy.position.posY += ennemy.direction.y * speed * deltaTime;

	ennemy.radius += 0.5 * cosf(ennemy.compteur);
}

bool LeaveScreenManager(SphereEnnemy& ennemy, sf::Vector2f currentPosition) {
	if ((currentPosition.x > -50 && currentPosition.x < 850) && (currentPosition.y > -50 && currentPosition.y < 650))
	{
		ennemy.hasBeenRendered = true;
	}
	else
	{
		if (ennemy.hasBeenRendered)
		{
			return true;
		}
	}

	return false;
}


float vecNorme(sf::Vector2f vector) {
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}

void Collisions(SphereEnnemy& ennemy, Player& player)
{
	float dx = ennemy.position.posX - player.pos._x + ennemy.radius - player.radius;
	float dy = ennemy.position.posY - player.pos._y + ennemy.radius - player.radius;
	float distance = sqrt(dx * dx + dy * dy);

	if (distance < ennemy.radius + ennemy.outlineThickness + player.radius)
	{
		player.newHit = (float)clock();
		if (player.newHit - player.lastHit > player.invincibleTime && player.isInvincible == true)
		{
			player.isInvincible == false;
			player.lastHit = player.newHit;
			if (player.shield <= 0)
			{
				player.shield = 0;
				ChangeLife(player, -1);
				player.isInvincible == true;
				std::cout << player.hp << std::endl;
			}
			else
			{
				ChangeShield(player, -1);
				player.isInvincible = true;
				std::cout << player.shield << std::endl;
			}
		}

	}
}

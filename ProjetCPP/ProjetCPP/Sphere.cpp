#include <iostream>;
#include <SFML/Graphics.hpp>;
#include "Sphere.hpp"

SphereEnnemy SphereCreator(float radius, float outlineThickness, sf::Color fillColor, sf::Color borderColor) {


	EnnemyPosition position;
	SphereEnnemy ennemy;

	sf::CircleShape ennemyShape;

	//definition position de depart
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

	//definition de la shape
	ennemy.shape.setOrigin(ennemy.position.posX, ennemy.position.posY);

	ennemy.shape = ennemyShape;
	ennemy.radius = radius;
	ennemy.outlineThickness = outlineThickness;
	ennemy.fillColor = fillColor;
	ennemy.borderColor = borderColor;

	//definition type de mouvement et couleur associee
	int randomNumber = rand() % 4 + 1;

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
	//case 3:
		//ennemy.movementType = MOVEMENT_TYPE::ZIGZAG;
		//ennemy.borderColor = sf::Color::Yellow;
		//break;
	case 3:
		ennemy.movementType = MOVEMENT_TYPE::DASH;
		ennemy.borderColor = sf::Color::Red;
		break;
	case 4:
		ennemy.movementType = MOVEMENT_TYPE::BREATHING;
		ennemy.borderColor = sf::Color::Yellow;
		break;
	default:
		break;
	}

	return ennemy;
}

void SphereMovementDefinition(SphereEnnemy& ennemy, Player& player) {
	//definition de la direction
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

	//normalisation du vecteur direction
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
		ennemy.shape.setOutlineColor(sf::Color::Green);
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

	ennemy.radius = ennemy.shape.getRadius();
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

//fonction de d?tection de collisions entre les ennemis et le Player
void Collisions(SphereEnnemy& ennemy, Player& player)
{
	sf::Vector2f ennemyPos = ennemy.shape.getPosition();
	float ennemyPosX = ennemyPos.x;
	float ennemyPosY = ennemyPos.y;
	sf::Vector2f playerPos = player.circle.getPosition();
	float playerPosX = playerPos.x;
	float playerPosY = playerPos.y;
	float dx = ennemyPosX - playerPosX + ennemy.shape.getRadius() - player.circle.getRadius();
	float dy = ennemyPosY - playerPosY + ennemy.shape.getRadius() - player.circle.getRadius();
	float distance = sqrt(dx * dx + dy * dy);

	if (distance < ennemy.shape.getRadius() + ennemy.shape.getOutlineThickness() + player.circle.getRadius()) // d?tection de si collision avec l'ennemi entr? en param?tre
	{
		player.newHit = (float)clock();
		if (player.newHit - player.lastHit > player.invincibleTime && player.isInvincible == true) // v?rification de si le temps d'invincibilit? est pass? ou non
		{
			player.isInvincible == false;
			player.lastHit = player.newHit;
			if (player.shield > 0)
			{
				ChangeShield(player, -1);
				player.isInvincible = true;
			}
			else if (player.hp > 0)
			{
				player.shield = 0;
				ChangeLife(player, -1);
				player.isInvincible == true;
				if (player.hp == 0)
				{
					player.isAlive = false;
				}
			}
		}

	}
}

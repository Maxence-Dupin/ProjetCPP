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


void SetUpPlayer(Player& player, int radius, float speed, int hp, int shield)
{
	player.circle.setRadius(radius);
	player.speed = speed;
	player.hp = hp;
	player.shield = shield;
}


// Gestion des déplacement d'un rectangle
void PlayerMouvement(Player& player, float deltaTime)
{
	float speed = player.speed; // 300 pixels par seconde

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))//up
		player.circle.move(sf::Vector2f(0.f, -speed * deltaTime));
		

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))//down
		player.circle.move(sf::Vector2f(0.f, speed * deltaTime));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))//right
		player.circle.move(sf::Vector2f(-speed * deltaTime, 0.f));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))//left
		player.circle.move(sf::Vector2f(speed * deltaTime, 0.f));
}

void ChangeLife(Player& player, int amout)
{
	player.hp += amout;
}

void ChangeShield(Player& player, int amout)
{
	player.shield += amout;
}


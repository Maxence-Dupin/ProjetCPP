#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Wall.h"


void CollisionWithWall(Player& player)
{
	if (player.circle.getPosition().x < 0)//left
		player.circle.setPosition(0.0f, player.circle.getPosition().y);

	if (player.circle.getPosition().y < 0)//top
		player.circle.setPosition(player.circle.getPosition().x, 0.0f);

	if (player.circle.getPosition().x + player.radius*2 > 800)//right
		player.circle.setPosition(800.0f - player.radius*2, player.circle.getPosition().y);

	if (player.circle.getPosition().y + player.radius*2 > 600)//bottom
		player.circle.setPosition(player.circle.getPosition().x, 600.0f - player.radius*2);


}
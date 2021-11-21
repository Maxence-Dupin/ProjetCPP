#pragma once
#include "GameOver.hpp"
#include "WaveManagement.hpp"
#include "Sphere.hpp"


//fonction réinitialisant toutes les caractéristiques du Player, du système de gestion de vague et supprimant les ennemis au relancement d'une partie
void RestartGame(Player& player, WaveState& waveState, std::vector<SphereEnnemy>& ennemyList)
{
	//Reinitialise Player
	player.pos._x = 400.0f;
	player.pos._y = 400.0f;
	player.circle.setPosition(player.pos._x, player.pos._y);
	player.maxHp = 3;
	player.hp = player.maxHp;
	player.maxShield = 3;
	player.shield = player.maxShield;
	player.speed = 300.0f;
	player.radius = 35.0f;
	player.circle.setRadius(player.radius);
	player.isAlive = true;
	player.invincibleTime = 500.0f;

	//Reinitialise Wave Management
	waveState.ennemyNumber = 3;
	waveState.waveNumber = 0;
	waveState.waveRunning = true;
	waveState.bonusTime = false;
	waveState.waveWaitTime = 2.0f;

	//Destroy all ennemies
	auto it = ennemyList.begin();
	while (it != ennemyList.end())
	{
		it = ennemyList.erase(it);
	}
}
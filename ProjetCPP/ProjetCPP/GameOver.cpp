#pragma once
#include "GameOver.hpp"
#include "WaveManagement.hpp"
#include "Sphere.hpp"

void RestartGame(Player& player, WaveState& waveState, std::vector<SphereEnnemy>& ennemyList)
{
	player.pos._x = 400.0f;
	player.pos._y = 400.0f;
	player.circle.setPosition(player.pos._x, player.pos._y);
	player.maxHp = 3;
	player.hp = player.maxHp;
	player.maxShield = 3;
	player.shield = player.maxShield;
	player.speed = 300.0f;
	player.radius = 25.0f;
	player.circle.setRadius(player.radius);
	player.isAlive = true;
	player.invincibleTime = 500.0f;

	waveState.ennemyNumber = 3;
	waveState.waveNumber = 0;
	waveState.waveRunning = true;
	waveState.bonusTime = false;
	waveState.waveWaitTime = 2.0f;

	auto it = ennemyList.begin();
	while (it != ennemyList.end())
	{
		it = ennemyList.erase(it);
	}
}
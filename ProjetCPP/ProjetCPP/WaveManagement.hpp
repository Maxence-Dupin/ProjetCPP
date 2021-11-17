#pragma once
#include <iostream>;
#include <SFML/Graphics.hpp>;
#include "Sphere.hpp";
#include "Player.hpp";

struct WaveState
{
	int ennemyNumber = 3;
	int waveNumber = 1; 
	bool waveRunning = true;
	bool bonusTime = true;
	float waveWaitTime = 2.0f;
};

bool LoadNextWave(WaveState& waveState, std::vector<SphereEnnemy>& ennemyList, Player& player);
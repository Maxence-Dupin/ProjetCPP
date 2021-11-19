#pragma once
#include <iostream>;
#include <SFML/Graphics.hpp>;
#include "Sphere.hpp";
#include "Player.hpp";

struct WaveState
{
	int ennemyNumber = 3;
	int waveNumber = 0; 
	bool waveRunning = true;
	bool bonusTime = false;
	float waveWaitTime = 2.0f;
};

bool LoadNextWave(WaveState& waveState, std::vector<SphereEnnemy>& ennemyList, Player& player);
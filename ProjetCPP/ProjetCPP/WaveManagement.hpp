#pragma once
struct WaveState
{
	int ennemyNumber = 3;
	int waveNumber = 0; 
	bool waveRunning = true;
	bool bonusTime = true;
	float waveWaitTime = 2.0f;
};

bool LoadNextWave(WaveState& waveState, std::vector<SphereEnnemy>& ennemyList, Player& player);
#pragma once
struct WaveState
{
	int ennemyNumber = 3;
	int waveNumber = 1; 
	bool waveRunning = true;
	float waveWaitTime = 2.0f;
};

bool LoadNextWave(WaveState& waveState, std::vector<SphereEnnemy>& ennemyList, Player& player);
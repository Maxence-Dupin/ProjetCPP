#pragma once
enum POWER_UP
{
	SIZE_DOWN = 0,
	SPEED_UP = 1,
	LIFE_UP = 2,
	SHIELD_UP = 3,
};

const int enumSize = 4;

void LoadBonusTime(int enumSize);
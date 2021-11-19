#pragma once
enum POWER_UP
{
	LIFE_UP,//green
	SIZE_DOWN,//red
	SPEED_UP,//yellow
	SHIELD_UP,//blue
};


const int enumSize = 4;


std::map<int, POWER_UP> LoadBonusTime(int enumSize);

void SizeDown(Player& player);
void SpeedBonus(Player& player);
void LifeUp(Player& player);
void ShieldUp(Player& player);

bool SelectBonus(std::map<int, POWER_UP> availablePowerUp, Player& player);
void ApplyBonus(int number, Player& player);



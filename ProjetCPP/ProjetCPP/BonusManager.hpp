#pragma once
enum POWER_UP
{
	SIZE_DOWN = 0,//green
	SPEED_UP = 1,//yellow
	LIFE_UP = 2,//red
	SHIELD_UP = 3,//blue
};



const int enumSize = 4;

std::map<int, POWER_UP> LoadBonusTime(int enumSize);

void SizeDown(Player& player);
void SpeedBonus(Player& player);
void LifeUp(Player& player);
void ShieldUp(Player& player);

void applyBonus(std::map<int, sf::RectangleShape> bonusVisu, int number, Player& player);



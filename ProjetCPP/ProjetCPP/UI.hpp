#pragma once
#include "player.hpp"

std::string getAssetsPath();
void UpdateHP(Player& player, sf::Text& text);
void UpdateShield(Player& player, sf::Text& text);
void UpdateWave(int waveNumber, sf::Text& text);

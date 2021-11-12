#include <iostream>;
#include <SFML/Graphics.hpp>;
#include  <windows.h>
#include "UI.hpp"
#include "Player.hpp"

std::string getAssetsPath()
{
    char cExeFilePath[256];
    GetModuleFileNameA(NULL, cExeFilePath, 256);
    std::string exeFilePath = cExeFilePath;
    int exeNamePos = exeFilePath.find_last_of("\\/");
    std::string appPath = exeFilePath.substr(0, exeNamePos + 1);
    std::string assetsPath = appPath + "\Assets\\";
    return assetsPath;
}

void UpdateHP(Player& player, sf::Text& text)
{
    auto hpString = std::to_string(player.hp);
    text.setString(hpString + " HP");
}

void UpdateShield(Player& player, sf::Text& text)
{
    auto shieldString = std::to_string(player.shield);
    text.setString("SHIELD : " + shieldString);
}

void UpdateWave(int waveNumber, sf::Text& text)
{
    auto waveString = std::to_string(waveNumber - 1);
    text.setString("WAVE  " + waveString);
}
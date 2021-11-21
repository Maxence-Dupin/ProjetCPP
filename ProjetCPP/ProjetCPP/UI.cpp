#include <iostream>;
#include <SFML/Graphics.hpp>;
#include <windows.h>
#include <shlwapi.h>
#include "UI.hpp"
#include "Player.hpp"

// fonction récupérant le chemin du dossier assets dans les dossiers Debug ou Release
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

// fonction récupérant le chemin du dossier assets à la racine du projet C++
std::string getAssetsPathFromRoot()
{
    char cExeFilePath[256];
    GetModuleFileNameA(NULL, cExeFilePath, 256);
    std::string exeFilePath = cExeFilePath;
    int exeNamePos = exeFilePath.find_last_of("\\/");
    std::string appPath = exeFilePath.substr(0, exeNamePos);
    exeNamePos = appPath.find_last_of("\\/");
    appPath = appPath.substr(0, exeNamePos + 1);
    std::string assetsPath = appPath + "\Assets\\";
    //std::cout << assetsPath << std::endl;
    return assetsPath;
}



//Fonctions pour update les textes en jeu

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
    auto waveString = std::to_string(waveNumber);
    text.setString("WAVE  " + waveString);
}
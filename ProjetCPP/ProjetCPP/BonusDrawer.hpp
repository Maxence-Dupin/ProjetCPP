#pragma once

struct BonusVisual
{
	std::vector<sf::ConvexShape> bonusShape;
	sf::RectangleShape bonusFrame;
	sf::CircleShape bonusCircle;
	sf::Text bonusLetter;
};

BonusVisual CircleAndFrameDraw(BonusVisual bonusVisual, float posX, float posY, sf::Color color);
BonusVisual HealBonusDraw(float posX, float posY);
BonusVisual SizeDownDraw(float posX, float posY);
BonusVisual SpeedUpDraw(float posX, float posY);
BonusVisual ShieldUpDraw(float posX, float posY);

void DrawBonus(sf::RenderWindow& window, float posX, float posY, int bonusNumber, std::string bonusLetter);
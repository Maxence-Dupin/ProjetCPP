#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>
#include "Player.hpp"
#include "UI.hpp"
#include "BonusManager.hpp"
#include "BonusDrawer.hpp"



BonusVisual CircleAndFrameDraw(BonusVisual bonusVisual, float posX, float posY, sf::Color color) 
{
	//definition frame et circle
	sf::RectangleShape bonusFrame;
	sf::CircleShape bonusCircle;

	// - - - FRAME 
	bonusFrame.setSize(sf::Vector2f(120.f, 180.f));
	bonusFrame.setOutlineThickness(5.f);
	bonusFrame.setOutlineColor(color);
	bonusFrame.setFillColor(sf::Color::Transparent);
	bonusFrame.setOrigin(bonusFrame.getSize() / 2.f);
	bonusFrame.setPosition(posX, posY);
	bonusFrame.rotate(10);

	// - - - CIRCLE
	float radius = 30.f;
	bonusCircle.setRadius(radius);
	bonusCircle.setOutlineThickness(5.f);
	bonusCircle.setOutlineColor(color);
	bonusCircle.setFillColor(sf::Color::Transparent);

	bonusCircle.setPosition(posX - radius, posY - radius);

	//attribution des shapes dans la structure
	bonusVisual.bonusFrame = bonusFrame;
	bonusVisual.bonusCircle = bonusCircle;

	return bonusVisual;
}

void DrawBonus(sf::RenderWindow& window, float posX, float posY, int bonusNumber)
{
	BonusVisual visualToDraw;

	switch (bonusNumber)
	{
	case POWER_UP::LIFE_UP:
		visualToDraw = HealBonusDraw(posX, posY);
		break;
	case POWER_UP::SIZE_DOWN:
		visualToDraw = SizeDownDraw(posX, posY);
		break;
	case POWER_UP::SPEED_UP:
		visualToDraw = SpeedUpDraw(posX, posY);	
		break;
	case POWER_UP::SHIELD_UP:
		visualToDraw = ShieldUpDraw(posX, posY);
		break;
	default:
		break;
	}
	 
	window.draw(visualToDraw.bonusFrame);
	window.draw(visualToDraw.bonusCircle);


	for (sf::ConvexShape oneComponent : visualToDraw.bonusShape) {
		window.draw(oneComponent);
	}
}


BonusVisual HealBonusDraw(float posX, float posY) 
{
	sf::Vector2f commonScale = sf::Vector2f(1.5f, 1.5f);

	//définition convexe shape
	sf::ConvexShape bonusShape;

	//definition de la structre visuelle
	BonusVisual bonusVisual;

	bonusVisual = CircleAndFrameDraw(bonusVisual, posX, posY, sf::Color::Green);

	// - - - SHAPE
	bonusShape.setPointCount(12);

	bonusShape.setPoint(0, sf::Vector2f(posX, posY));
	bonusShape.setPoint(1, sf::Vector2f(posX + 10, posY));
	bonusShape.setPoint(2, sf::Vector2f(posX + 10, posY - 10));
	bonusShape.setPoint(3, sf::Vector2f(posX + 20, posY - 10));
	bonusShape.setPoint(4, sf::Vector2f(posX + 20, posY));
	bonusShape.setPoint(5, sf::Vector2f(posX + 30, posY));
	bonusShape.setPoint(6, sf::Vector2f(posX + 30, posY + 10));
	bonusShape.setPoint(7, sf::Vector2f(posX + 20, posY + 10));
	bonusShape.setPoint(8, sf::Vector2f(posX + 20, posY + 20));
	bonusShape.setPoint(9, sf::Vector2f(posX + 10, posY + 20));
	bonusShape.setPoint(10, sf::Vector2f(posX + 10, posY + 10));
	bonusShape.setPoint(11, sf::Vector2f(posX, posY + 10));

	bonusShape.setOutlineThickness(3.0f);
	bonusShape.setOutlineColor(sf::Color::Green);
	bonusShape.setFillColor(sf::Color::Transparent);

	bonusShape.setPosition(bonusShape.getPosition() - sf::Vector2f(15.0f, 5.0f));

	//attribution des shapes dans la structure
	bonusVisual.bonusShape.push_back(bonusShape);

	return bonusVisual;
}

BonusVisual SizeDownDraw(float posX, float posY)
{
	sf::Vector2f commonScale = sf::Vector2f(1.5f, 1.5f);

	//définition des 2 shapes
	sf::ConvexShape bonusShapeLeftArrow, bonusShapeRightArrow;

	//definition de la structre visuelle
	BonusVisual bonusVisual;

	bonusVisual = CircleAndFrameDraw(bonusVisual, posX, posY, sf::Color::Red);

	// - - - SHAPE LEFT ARROW
	bonusShapeLeftArrow.setPointCount(6);

	bonusShapeLeftArrow.setPoint(0, sf::Vector2f(posX, posY));
	bonusShapeLeftArrow.setPoint(5, sf::Vector2f(posX + 5.f, posY - 10.f));
	bonusShapeLeftArrow.setPoint(4, sf::Vector2f(posX + 10.f, posY - 10.f));
	bonusShapeLeftArrow.setPoint(3, sf::Vector2f(posX + 5.f, posY));
	bonusShapeLeftArrow.setPoint(2, sf::Vector2f(posX + 10.f, posY + 10.f));
	bonusShapeLeftArrow.setPoint(1, sf::Vector2f(posX + 5.f, posY + 10.f));

	bonusShapeLeftArrow.setPosition(bonusShapeLeftArrow.getPosition() + sf::Vector2f(5.f, 0.f));

	bonusVisual.bonusShape.push_back(bonusShapeLeftArrow);

	// - - - SHAPE RIGHT ARROW
	bonusShapeRightArrow.setPointCount(6);

	bonusShapeRightArrow.setPoint(0, sf::Vector2f(posX, posY));
	bonusShapeRightArrow.setPoint(1, sf::Vector2f(posX - 5.f, posY - 10.f));
	bonusShapeRightArrow.setPoint(2, sf::Vector2f(posX - 10.f, posY - 10.f));
	bonusShapeRightArrow.setPoint(3, sf::Vector2f(posX - 5.f, posY));
	bonusShapeRightArrow.setPoint(4, sf::Vector2f(posX - 10.f, posY + 10.f));
	bonusShapeRightArrow.setPoint(5, sf::Vector2f(posX - 5.f, posY + 10.f));


	bonusShapeRightArrow.setPosition(bonusShapeRightArrow.getPosition() - sf::Vector2f(5.f, 0.f));
	
	bonusVisual.bonusShape.push_back(bonusShapeRightArrow);


	//application des couleurs
	for (sf::ConvexShape& oneSaphe : bonusVisual.bonusShape) {
		oneSaphe.setOutlineThickness(3.0f);
		oneSaphe.setOutlineColor(sf::Color::Red);
		oneSaphe.setFillColor(sf::Color::Transparent);
	}
	
	return bonusVisual;
}

BonusVisual SpeedUpDraw(float posX, float posY) 
{
	sf::Vector2f commonScale = sf::Vector2f(1.5f, 1.5f);

	//définition convexe shape
	sf::ConvexShape arrowTop, arrowBottom;

	//definition de la structre visuelle
	BonusVisual bonusVisual;

	bonusVisual = CircleAndFrameDraw(bonusVisual, posX, posY, sf::Color::Yellow);

	// - - - ARROW TOP + BOTTOM
	arrowTop.setPointCount(6);

	arrowTop.setPoint(5, sf::Vector2f(posX, posY));
	arrowTop.setPoint(4, sf::Vector2f(posX + 10.f, posY + 5.f));
	arrowTop.setPoint(3, sf::Vector2f(posX + 10.f, posY + 10.f));
	arrowTop.setPoint(2, sf::Vector2f(posX, posY + 5.f));
	arrowTop.setPoint(1, sf::Vector2f(posX - 10.f, posY + 10.f));
	arrowTop.setPoint(0, sf::Vector2f(posX - 10.f, posY + 5.f));

	arrowBottom = arrowTop;

	arrowTop.setPosition(arrowTop.getPosition() - sf::Vector2f(0.f, 15.f));
	arrowBottom.setPosition(arrowBottom.getPosition() + sf::Vector2f(0.f, 5.f));

	bonusVisual.bonusShape.push_back(arrowTop);
	bonusVisual.bonusShape.push_back(arrowBottom);

	//application des couleurs
	for (sf::ConvexShape& oneSaphe : bonusVisual.bonusShape) {
		oneSaphe.setOutlineThickness(3.0f);
		oneSaphe.setOutlineColor(sf::Color::Yellow);
		oneSaphe.setFillColor(sf::Color::Transparent);
	}

	return bonusVisual;
}

BonusVisual ShieldUpDraw(float posX, float posY) 
{
	sf::Vector2f commonScale = sf::Vector2f(1.5f, 1.5f);

	//définition des 2 shapes
	sf::ConvexShape shieldBorder, shieldInside;

	//definition de la structre visuelle
	BonusVisual bonusVisual;

	bonusVisual = CircleAndFrameDraw(bonusVisual, posX, posY, sf::Color::Blue);

	// - - - SHIELD BORDER
	shieldBorder.setPointCount(10);

	shieldBorder.setPoint(0, sf::Vector2f(posX, posY));
	shieldBorder.setPoint(1, sf::Vector2f(posX - 12.5f, posY + 2.5f));
	shieldBorder.setPoint(2, sf::Vector2f(posX - 15.f, posY + 5.f));
	shieldBorder.setPoint(3, sf::Vector2f(posX - 15.f, posY + 10.f));
	shieldBorder.setPoint(4, sf::Vector2f(posX - 10.f, posY + 25.f));
	shieldBorder.setPoint(5, sf::Vector2f(posX, posY + 32.5f));
	shieldBorder.setPoint(6, sf::Vector2f(posX + 10.f, posY + 25.f));
	shieldBorder.setPoint(7, sf::Vector2f(posX + 15.f, posY + 10.f));
	shieldBorder.setPoint(8, sf::Vector2f(posX + 15.f, posY + 5.f));
	shieldBorder.setPoint(9, sf::Vector2f(posX + 12.5f, posY + 2.5f));

	shieldBorder.setPosition(shieldBorder.getPosition() - sf::Vector2f(0.f, 15.f));

	bonusVisual.bonusShape.push_back(shieldBorder);

	//application des couleurs
	for (sf::ConvexShape& oneSaphe : bonusVisual.bonusShape) {
		oneSaphe.setOutlineThickness(3.0f);
		oneSaphe.setOutlineColor(sf::Color::Blue);
		oneSaphe.setFillColor(sf::Color::Transparent);
	}

	return bonusVisual;
}

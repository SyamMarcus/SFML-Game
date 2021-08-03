#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

#define MAX_NUMBER_OF_ITEMS 4

class UpgradeMenu
{
public:
	UpgradeMenu(float _width, float _height);
	~UpgradeMenu();

	void Update(sf::Vector2f _viewSize, int _money);

	void MoveUp();

	void MoveDown();

	void Draw(sf::RenderWindow &window);

	int  GetPressedItem() { return selectedItemIndex; };

private:

	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::Text moneyText;
	float width;
	float height;

};


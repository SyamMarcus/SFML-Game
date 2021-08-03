#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

#define MAX_NUMBER_OF_ITEMS 3

class Menu
{
public:
	Menu(float _width, float _height);
	~Menu();

	void Update(sf::Vector2f _viewCen);

	void MoveUp();
	void MoveDown();
	void Draw(sf::RenderWindow &window);
	int  GetPressedItem() { return selectedItemIndex; };

private:

	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	float width;
	float height;
};


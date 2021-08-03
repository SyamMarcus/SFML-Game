#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

#define MAX_NUMBER_OF_ITEMS 2

class DeathScreen
{
public:
	DeathScreen(float _width, float _height);
	~DeathScreen();

	void Update(sf::Vector2f _viewSize, float deltaTime);

	void Draw(sf::RenderWindow &window);


	int  GetPressedItem() { return selectedItemIndex; };

private:
	sf::RectangleShape body;

	float alphaTimer;

	int alpha;
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	float width;
	float height;
};
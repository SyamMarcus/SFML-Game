#pragma once
#include "SFML/Graphics.hpp"

class Background
{
public:
	Background(sf::Texture * texture);
	~Background();

	void Draw(sf::RenderWindow& window);

private: 
	
	sf::RectangleShape body;

};


#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

class Reticle
{
public:
	Reticle(sf::Texture * texture, sf::Vector2u _winSize);
	~Reticle();

	void Update(sf::Vector2i _mousePos, sf::Vector2u _winSize);

	void Draw(sf::RenderWindow& window);

private:

	sf::RectangleShape body;
	sf::Vector2f reticle;

};


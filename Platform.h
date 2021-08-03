#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

class Platform
{
public:
	/*Constructor takes a few variables to display platforms*/
	Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	~Platform();
	
	/*This creates a draw function which takes a reference to the window to be drawn to*/
	void Draw(sf::RenderWindow& window);
	
	/*getter function for body collision*/
	Collider GetCollider() { return Collider(body); }

private:

	/*private body variable for the platform*/
	sf::RectangleShape body;

};


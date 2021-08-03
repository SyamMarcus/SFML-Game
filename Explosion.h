#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include <iostream>

class Explosion
{
public:
	Explosion(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
		~Explosion();

	void Update(float deltaTime);

	bool GetEraseSet() { return eraseSet; }

	Collider GetCollider() { return Collider(body); }

	void Draw(sf::RenderWindow & window);

private:
	sf::RectangleShape body;

	float explosionTimer;	
	
	bool eraseSet;
};


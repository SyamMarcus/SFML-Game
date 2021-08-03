#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Projectile.h"
#include "Random.h"

class Shotgun
{
public:
	Shotgun(sf::Texture * texture);
	~Shotgun();

	void Update(float deltaTime, sf::Vector2f _playerPos, sf::Vector2i _mousePos, sf::Vector2u _winSize);

	void Draw(sf::RenderWindow& window);

private:

	std::vector<Projectile> projectileVec;
	float shotTimer;
};


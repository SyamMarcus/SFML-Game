#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include "Random.h"
#include "Player.h"
#include "Collider.h"


class Rpg
{
public:
	Rpg(sf::Texture * texture);

	~Rpg();

	void Update(float deltaTime, sf::Vector2f _playerPos, sf::Vector2i _mousePos, sf::Vector2u _winSize);

	void Draw(sf::RenderWindow& window);

	Collider GetCollider();

	sf::Vector2f GetPosition();

	int GetProjCount() { return projectileVec.size(); }

	bool GetEraseSet() { return eraseSet; }

private:

	std::vector<Projectile> projectileVec;

	bool eraseSet;
	int pistolCount;

};


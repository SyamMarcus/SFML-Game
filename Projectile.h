#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include "Collider.h"
#include "Player.h"
#include <iostream>

class Projectile
{
public:
	Projectile(sf::Texture * texture);

	Projectile(sf::Texture * texture, float _speed);

	~Projectile();

	void Update(float deltaTime, sf::Vector2f _playerPos, sf::Vector2i _mousePos, sf::Vector2u _winSize);

	void Draw(sf::RenderWindow& window);

	bool GetEraseSet() { return eraseSet; }

	Collider GetCollider() { return Collider(body); }

	sf::Vector2f GetPosition() { return body.getPosition(); }

private:

	sf::RectangleShape body;

	sf::Vector2f direction;
	sf::Vector2f normalDirection;
	float speed;

	int setTextureDistance;
	bool textureSet;
	bool eraseSet;

	bool inputReady;
	sf::Vector2f initPos;

	bool moveReady;
};


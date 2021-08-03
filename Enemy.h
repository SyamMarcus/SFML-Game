#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
#include "Random.h"
#include "Detection.h"


class Enemy
{
public:
	
	Enemy(sf::Texture* texture, sf::Vector2u _imageCount, float _switchTime, float _speed);
	
	~Enemy();


	void Update(float deltaTime, bool _detect, sf::Vector2f _playerPos);

	void Draw(sf::RenderWindow& window);
	
	void Damage();

	void Damage(float multiplier);

	bool GetAlive() { return alive; }

	int GetHealth() { return health; }

	sf::Vector2f GetPosition() { return body.getPosition(); }

	Collider GetCollider() { return Collider(body); }

	Detection GetDetection() { return Detection(body); }


private:

	sf::RectangleShape body;
	Animation animation;
	float speed;

	double PI = 3.1415926535897;

	bool alive;
	int health;

	unsigned int row;
	bool faceLeft;
	float damageTimer;
	float moveSwitch;
	float totalTime;
	float switchTime;

	bool moveLeft;
	bool moveRight;
	bool moveUp;
	bool moveDown;
};


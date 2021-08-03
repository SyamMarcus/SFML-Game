#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
#include "Detection.h"
#include "Projectile.h"

class Player
{
public:

	/*This will take the same variables from the animation class. It also takes a speed value*/
	Player(sf::Texture* texture, sf::Texture * legTexture, sf::Vector2u _imageCount, float _switchTime, float _speed);
	~Player();

	/*This creates an update function taking delta time*/
	void Update(float deltaTime, sf::Vector2i _mousePos, sf::Vector2u _winSize);

	void Damage();

	void Damage(float multiplier);

	int GetHealth() { return health; }

	/*This creates a draw function which takes a reference to the window to be drawn to*/
	void Draw(sf::RenderWindow& window);

	/*simple getter functuion to return a private variable value*/
	sf::Vector2f GetPosition() { return body.getPosition(); }

	/*getter function for body collision*/
	Collider GetCollider() { return Collider(body); }

	Detection GetDetection() { return Detection(body); }

private:

	/* This initalises some private variables, a rect shape for the player, a new Animation object called animation (for init list),
	a speed float for animation speed, the row the current sprites will use (unsigned because row will never be -)
	a bool which is set if the sprite faces left*/
	sf::RectangleShape body;
	sf::RectangleShape legBody;
	Animation animation;
	float speed;
	unsigned int row;
	bool faceLeft;

	float damageTimer;
	bool alive;
	int health;

	double PI = 3.1415926535897;

};



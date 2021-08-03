#include "Player.h"
#include "Animation.h"
#include <iostream>

/*This contructor uses an initalisation list from Animation class*/
Player::Player(sf::Texture * texture, sf::Texture * legTexture, sf::Vector2u _imageCount, float _switchTime, float _speed) :
	animation(legTexture, _imageCount, _switchTime)
{
	/*Setting values for variables*/
	damageTimer = 0.0f;
	health = 200;
	alive = true;
	speed = _speed;
	row = 0;
	faceLeft = true;

	/*setting the initial position,texture,center and size of the player rectangle shape */
	body.setPosition(0.0f, 0.0f);
	body.setSize(sf::Vector2f(32.0f, 32.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(texture);

	legBody.setTexture(legTexture);
	legBody.setPosition(0.0f, 0.0f);
	legBody.setSize(sf::Vector2f(32.0f, 32.0f));
	legBody.setOrigin(legBody.getSize() / 2.0f);
	
}

Player::~Player()
{
}

void Player::Update(float deltaTime, sf::Vector2i _mousePos, sf::Vector2u _winSize)
{

	damageTimer += deltaTime;

	sf::Vector2f playerPos = body.getPosition();
	sf::Vector2i mousePos = _mousePos;	
	sf::Vector2u winSize = _winSize;
	sf::Vector2f viewCen;
	viewCen.x = winSize.x / 2;
	viewCen.y = winSize.y / 2;

	sf::Vector2f movement(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		movement.x -= speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		movement.x += speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		movement.y -= speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		movement.y += speed * deltaTime;


	if (movement.x == 0)
		row = 0; 
	else
	{
		row = 1;
		if (movement.x < 0)
			faceLeft = true;
		else
			faceLeft = false;
	}
	if (movement.y < 0)
		row = 2;
	if (movement.y > 0)
		row = 3;

	
	float angle = atan2(mousePos.y - viewCen.y, mousePos.x - viewCen.x);
	angle = angle * (180 / PI);
	//std::cout << "angle: " << angle << std::endl;
	body.setRotation(angle);

	animation.Update(row, deltaTime, faceLeft);
	legBody.setTextureRect(animation.uvRect);
	
	body.move(movement);
	legBody.setPosition(body.getPosition());
}

void Player::Damage()
{
	if (alive && damageTimer >= 0.2f)
	{
		damageTimer = 0.0f;
		health = health - 10;
		if (health <= 0)
		{
			alive = false;
		}
	}
}

void Player::Damage(float multiplier)
{
	if (alive && damageTimer >= 0.2f)
	{
		damageTimer = 0.0f;
		health = health - (10 * multiplier);
		if (health <= 0)
		{
			alive = false;
		}
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(legBody);
	window.draw(body);
}

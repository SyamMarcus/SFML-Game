#include "Enemy.h"


Enemy::Enemy(sf::Texture* texture, sf::Vector2u _imageCount, float _switchTime, float _speed) :
	animation(texture, _imageCount, _switchTime)
{
	damageTimer = 0.0f;
	health = 100;
	alive = true;
	moveSwitch = 0.5f;
	totalTime = 0;
	row = 0;
	faceLeft = true;

	Random speedRan(0, 20);
	speed = _speed + speedRan.GetRandNum();

	Random spawn(0, 300);
	body.setPosition(spawn.GetRandNum(), spawn.GetRandNum());
	body.setSize(sf::Vector2f(24.0f, 24.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(texture);
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime, bool _detect, sf::Vector2f _playerPos)
{
	damageTimer += deltaTime;
	sf::Vector2f playerPos = _playerPos;
	bool detect = _detect;
	sf::Vector2f movement(0.0f, 0.0f);

	totalTime += deltaTime;
	Random ran(1, 4);

	if (totalTime >= moveSwitch)
	{
		moveLeft = false;
		moveRight = false;
		moveUp = false;
		moveDown = false;

		if (detect == false)
		{
			switch (ran.GetRandNum())
			{
				case 1:
				{
					moveLeft = true;
					break;
				}
				case 2:
				{
					moveRight = true;
					break;
				}
				case 3:
				{
					moveUp= true;
					break;
				}
				case 4:
				{
					moveDown = true;
					break;
				}
			}
		}
		else
		{
			// change row to an attack/chase animation
		}

		totalTime -= moveSwitch;
	}

	if (moveLeft)	
		movement.x -= speed * deltaTime;
	if (moveRight)
		movement.x += speed * deltaTime;
	if (moveUp)
		movement.y -= speed * deltaTime;
	if (moveDown)
		movement.y += speed * deltaTime;

	if (movement.x < 0)
		body.setRotation(180);
	if (movement.x > 0)
		body.setRotation(0);
	if (movement.y < 0)
		body.setRotation(270);
	if (movement.y > 0)
		body.setRotation(90);
	
	if (detect)
	{
		float angle = atan2(playerPos.y - body.getPosition().y, playerPos.x - body.getPosition().x);
		angle = angle * (180 / PI);
		//std::cout << "angle: " << angle << std::endl;
		body.setRotation(angle);
	}

	body.move(movement);
}

void Enemy::Draw(sf::RenderWindow & window)
{
	window.draw(body);
}

void Enemy::Damage() //USE AN OVERLOAD DAMAGE MULTIPLIER OF BASE 10 FOR ALL DAMAGE, TURN HEALTH AND DAMAGE INTO A FLOAT.
{
	if (alive && damageTimer >= 0.2f)
	{
		damageTimer = 0.0f;
		health = health - 10;
		if (health <= 0)
			alive = false;
	}
}

void Enemy::Damage(float multiplier) //USE AN OVERLOAD DAMAGE MULTIPLIER OF BASE 10 FOR ALL DAMAGE, TURN HEALTH AND DAMAGE INTO A FLOAT.
{
	if (alive && damageTimer >= 0.2f)
	{
		damageTimer = 0.0f;
		health = health - (10 * multiplier);
		if (health <= 0)
			alive = false;
	}
}
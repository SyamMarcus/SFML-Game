#include "Projectile.h"


Projectile::Projectile(sf::Texture * texture) 
{
	inputReady = true;
	speed = 1.5f;
	setTextureDistance = 18;
	eraseSet = false;

	textureSet = false;

	body.setSize(sf::Vector2f(10.0f, 10.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(texture);
}

Projectile::Projectile(sf::Texture * texture, float _speed)
{
	inputReady = true;
	speed = _speed;
	setTextureDistance = 18;
	eraseSet = false;

	textureSet = false;

	body.setSize(sf::Vector2f(10.0f, 10.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(texture);
}

Projectile::~Projectile()
{
}

void Projectile::Update(float deltaTime, sf::Vector2f _playerPos, sf::Vector2i _mousePos, sf::Vector2u _winSize)
{	
	sf::Vector2f movement(0.0f, 0.0f);
	sf::Vector2i mousePos = _mousePos;
	sf::Vector2u winSize = _winSize;
	sf::Vector2f viewCen;
	viewCen.x = winSize.x / 2;
	viewCen.y = winSize.y / 2;
	float modulus = 0.0f;


	if (inputReady)
	{
		moveReady = false;

		initPos = _playerPos; 
		body.setPosition(initPos);

			//std::cout << "MOUSE X: " << mousePos.x << " MOUSE Y: " << mousePos.y << std::endl;
			direction.x = mousePos.x - viewCen.x;
			direction.y = mousePos.y - viewCen.y;
			
			//  BREAKS IF MOUSE POSITION IS (0,0) 
			modulus = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
			normalDirection.x = direction.x / modulus;
			normalDirection.y = direction.y / modulus;

			moveReady = true;
			inputReady = false;
	}

	if (moveReady)
	{
		movement.x = normalDirection.x * 0.5;
		movement.y = normalDirection.y * 0.5;
		//d::cout << "movement X: " << movement.x << " movement Y: " << movement.y << std::endl;
	}

	sf::Vector2f distance;
	distance.x = (body.getPosition().x - initPos.x);
	distance.y = (body.getPosition().y - initPos.y);
	if ((distance.x > setTextureDistance || distance.y > setTextureDistance) || (-distance.x > setTextureDistance || -distance.y > setTextureDistance))
		textureSet = true;

	int setEraseDistance;
	int winErase = std::max(winSize.x, winSize.y);
	if ((distance.x > winErase || distance.y > winErase) || (-distance.x > winErase || -distance.y > winErase))
	{
		eraseSet = true;
	}

	body.move(movement);
}


void Projectile::Draw(sf::RenderWindow & window)
{
	if (textureSet)
		window.draw(body);
}

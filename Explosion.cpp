#include "Explosion.h"



Explosion::Explosion(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
	eraseSet = false;
	explosionTimer = 0.0f;

	body.setTexture(texture);
	body.setOrigin(size / 2.0f);
	body.setSize(size);
	body.setPosition(position);
}

Explosion::~Explosion()
{
}

void Explosion::Update(float deltaTime)
{
	explosionTimer += deltaTime;
	if (explosionTimer >= 1.25f)
	{
		eraseSet = true;
	}
	//std::cout << explosionTimer << std::endl;
}

void Explosion::Draw(sf::RenderWindow & window)
{
	window.draw(body);
}
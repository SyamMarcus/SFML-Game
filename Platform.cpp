#include "Platform.h"




Platform::Platform(sf::Texture * texture, sf::Vector2f size, sf::Vector2f position)
{
	body.setTexture(texture);
	body.setOrigin(size / 2.0f);
	body.setSize(size);
	body.setPosition(position);
}

Platform::~Platform()
{
}

void Platform::Draw(sf::RenderWindow & window)
{
	window.draw(body);
}

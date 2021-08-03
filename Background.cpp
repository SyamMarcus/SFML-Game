#include "Background.h"



Background::Background(sf::Texture * texture)
{
	body.setPosition(0.0f, 0.0f);
	body.setSize(sf::Vector2f(980.0f, 980.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(texture);
}

Background::~Background()
{
}

void Background::Draw(sf::RenderWindow & window)
{
	window.draw(body);
}

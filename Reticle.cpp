#include "Reticle.h"



Reticle::Reticle(sf::Texture * texture, sf::Vector2u _winSize)
{

	body.setPosition(0.0f, 0.0f);
	body.setSize(sf::Vector2f(32.0f, 32.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(texture);

}


Reticle::~Reticle()
{
}

void Reticle::Update(sf::Vector2i _mousePos, sf::Vector2u _winSize)
{
	sf::Vector2i mousePos = _mousePos;
	sf::Vector2u winSize = _winSize;
	sf::Vector2f viewCen;
	viewCen.x = winSize.x / 2;
	viewCen.y = winSize.y / 2;

	reticle.x = mousePos.x;
	reticle.y = mousePos.y;
	

	body.setPosition(reticle);

	//std::cout << mousePos.x << " - " << mousePos.y << std::endl;
}

void Reticle::Draw(sf::RenderWindow & window)
{
	window.draw(body);
}

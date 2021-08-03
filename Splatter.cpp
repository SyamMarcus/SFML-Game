#include "Splatter.h"



Splatter::Splatter(sf::Texture* texture, sf::Vector2f _bodyPosition)
{
	//bodyPosition = _bodyPosition;
	
	body.setTexture(texture);
	body.setPosition(_bodyPosition);
	body.setSize(sf::Vector2f(32.0f, 32.0f));
	body.setOrigin(body.getSize() / 2.0f);
	
}

Splatter::Splatter(sf::Texture * texture, sf::Vector2f _bodyPosition, sf::Vector2u _imageCount)
{
	imageCount = _imageCount;

	body.setPosition(_bodyPosition);
	body.setSize(sf::Vector2f(32.0f, 32.0f));
	body.setOrigin(body.getSize() / 2.0f);

	uvRect.width  = (*texture).getSize().x / float(imageCount.x);
	uvRect.height = (*texture).getSize().y / float(imageCount.y);

	uvRect.top = uvRect.height * 2;
	uvRect.left = uvRect.width * 2;

	body.setTextureRect(uvRect);
}

Splatter::Splatter(int textureChance, sf::Vector2f _bodyPosition, sf::Texture * texture1, sf::Texture * texture2, 
	sf::Texture * texture3, sf::Texture * texture4, sf::Texture * texture5, sf::Texture * texture6, 
	sf::Texture * texture7, sf::Texture * texture8, sf::Texture * texture9)
{
	Random splatterChanceRan(1, textureChance);

	if (splatterChanceRan.GetRandNum() == 1)
	{	
		Random splatterTextureRan(1, 9);

		body.setPosition(_bodyPosition);
		body.setSize(sf::Vector2f(32.0f, 32.0f));
		body.setOrigin(body.getSize() / 2.0f);

		if (splatterTextureRan.GetRandNum() == 1)
			body.setTexture(texture1);
		if (splatterTextureRan.GetRandNum() == 2)
			body.setTexture(texture2);
		if (splatterTextureRan.GetRandNum() == 3)
			body.setTexture(texture3);
		if (splatterTextureRan.GetRandNum() == 4)
			body.setTexture(texture4);
		if (splatterTextureRan.GetRandNum() == 5)
			body.setTexture(texture5);
		if (splatterTextureRan.GetRandNum() == 6)
			body.setTexture(texture6);
		if (splatterTextureRan.GetRandNum() == 7)
			body.setTexture(texture7);
		if (splatterTextureRan.GetRandNum() == 8)
			body.setTexture(texture8);
		if (splatterTextureRan.GetRandNum() == 9)
			body.setTexture(texture9);
	}
}

Splatter::~Splatter()
{
}

void Splatter::Update()
{
	//sf::Vector2f bodyPosition = _bodyPostition;
	//body.setPosition(bodyPosition);
	//printf("YEET");
	//uvRect.left = uvRect.height * currentImage.x;
}

void Splatter::Draw(sf::RenderWindow & window)
{
	window.draw(body);
}

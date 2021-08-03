#pragma once
#include "SFML/Graphics.hpp"
#include "Random.h"

class Splatter
{
public:
	Splatter(sf::Texture* texture, sf::Vector2f _bodyPosition);

	Splatter(sf::Texture* texture, sf::Vector2f _bodyPosition, sf::Vector2u _imageCount);

	Splatter(int textureChance, sf::Vector2f _bodyPosition, sf::Texture * texture1, sf::Texture * texture2, 
		sf::Texture * texture3, sf::Texture * texture4, sf::Texture * texture5, sf::Texture * texture6,
		sf::Texture * texture7, sf::Texture * texture8, sf::Texture * texture9);

	~Splatter();

	void Update();

	void Draw(sf::RenderWindow& window);

private:
	
	sf::RectangleShape body;
	sf::Vector2f bodyPosition;

	sf::Vector2u imageCount;
	sf::Vector2u currentImage;
	sf::IntRect uvRect;
};


#pragma once
#include <SFML/Graphics.hpp>


class Animation
{
public:

	/*This takes a reference to the texture being loaded, the dimentions of the sprite sheet and the animation time cycle*/
	Animation(sf::Texture* texture, sf::Vector2u _imageCount, float _switchTime);
	~Animation();

	/*This initialises a Update function*/
	void Update(int row, float deltaTime, bool faceLeft);

	void UpdateFlat(int row, float deltaTime, bool faceLeft, sf::Vector2f _playerPos, sf::Vector2i _mousePos);

	/*This initialises a variable whith can store the "Left" and "Top" coordinate of the rectangle
	as well as the "width" and "height"(pixels).*/
	sf::IntRect uvRect;

private:

	/*This initalises private variables for the dimentions of the sprite sheet and image being displayed*/
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	/*This initalises private varialbes for animation cycle times*/
	float totalTime;
	float switchTime;
};


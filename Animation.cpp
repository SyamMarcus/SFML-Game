#include "Animation.h"


Animation::Animation(sf::Texture* texture, sf::Vector2u _imageCount, float _switchTime)
{
	/*Sets values to the respective private variables*/
	imageCount = _imageCount;
	switchTime = _switchTime;

	totalTime = 0;
	currentImage.x = 0;

	/*This calculates the width and height of an individual sprite on a sprite sheet and sets them to uvRect*/
	uvRect.width  = (* texture).getSize().x / float(imageCount.x);
	uvRect.height = (* texture).getSize().y / float(imageCount.y);

}

Animation::~Animation()
{
}

void Animation::Update(int row, float deltaTime, bool faceLeft)
{
	/*This sets the row for the current image cycles*/
	currentImage.y = row;

	/*This adds the current cycle's delta time to the total time*/
	totalTime += deltaTime;

	/*When the total time has added enough delta time to be greater than (or equal) switch time*/
	if (totalTime >= switchTime)
	{
		//This resets the total time and cycles the current sprite to the next one*/
		totalTime -= switchTime;
		currentImage.x++;

		/*If the current image is larger than the amount of sprites, reset to the first sprite*/
		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
		}
	}

	uvRect.top = uvRect.height * currentImage.y;

	/*These are absolute values to ensure that there are no small displacements which can cause 
	the animation to flicker between 2 different sprites*/

	if (faceLeft)
	{
		uvRect.left = uvRect.width * currentImage.x;
		uvRect.width = abs(uvRect.width);
	}
	else
	{
		uvRect.left = abs(uvRect.width) * (currentImage.x + 1);
		uvRect.width = -abs(uvRect.width);
	}

}

void Animation::UpdateFlat(int row, float deltaTime, bool faceLeft, sf::Vector2f _playerPos, sf::Vector2i _mousePos)
{
	sf::Vector2f playerPos = _playerPos;
	sf::Vector2i mousePos = _mousePos;

	currentImage.y = row;

	/*This adds the current cycle's delta time to the total time*/
	totalTime += deltaTime;

	/*When the total time has added enough delta time to be greater than (or equal) switch time*/
	if (totalTime >= switchTime)
	{
		//This resets the total time and cycles the current sprite to the next one*/
		totalTime -= switchTime;
		currentImage.x++;

		/*If the current image is larger than the amount of sprites, reset to the first sprite*/
		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
		}
	}

	uvRect.top = uvRect.height * currentImage.y;
	
	

	



}

#include "Detection.h"


Detection::Detection(sf::RectangleShape& body) :
	body(body)
{
}


Detection::~Detection()
{
}

bool Detection::CheckDetection(Detection & other, float deltaTime, float _speed)
{
	Random speedRan(0, 20);
	speed = _speed + speedRan.GetRandNum();

	sf::Vector2f otherPosition = other.GetPosition();
	sf::Vector2f otherHalfSize = other.GetHalfSize();
	sf::Vector2f thisPosition = GetPosition();
	sf::Vector2f thisHalfSize = GetHalfSize();
	
	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;
	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if ((intersectX < 50.0f && intersectY < 50.0f) || detect == true)
	{
		
		if (intersectX > intersectY)
		{
			if (deltaX > 0.0f)
			{
				Move(speed * deltaTime, 0.0f);
			}
			else
			{
				Move(-speed * deltaTime, 0.0f);
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				Move(0.0f, speed * deltaTime);
			}
			else
			{
				Move(0.0f, -speed * deltaTime);
			}
		}
		detect = true;
		return true;
	}
	if (detect != true)
	{
		detect = false;
		return false;
	}
}


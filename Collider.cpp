#include "Collider.h"
#include "Player.h"



Collider::Collider(sf::RectangleShape& body) : 
	body(body)
{
}

Collider::~Collider()
{
}

bool Collider::CheckCollision(Collider& other, float push)
{	
	/*These set variables with values to calculate the delta and intersect of an object*/
	sf::Vector2f otherPosition = other.GetPosition();
	sf::Vector2f otherHalfSize = other.GetHalfSize();
	sf::Vector2f thisPosition  = GetPosition();
	sf::Vector2f thisHalfSize  = GetHalfSize();

	/*The delta of two objects is the distance between the two object centers. We use absolute values
	so that the calculation is not effected by which object is in front of the other. we use the two 
	half sizes of the boxes to check if the delta of either of the two boxes are smaller that the sum
	of the two half sizes because that would mean that the edges boxes are inside one another*/
	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;
	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);


	/*this checks to see if the boxes are colliding returning true or false*/
	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		/*This is a clamp, we take the max value of either "push" or 0 (push can be any number > 0),
		and take the min value of either 1 or push. This ensures that 0 < push < 1. This limits the 
		amount an object can be pushed so objects dont push each other too far away.*/
		push = std::min(std::max(push, 0.0f), 1.0f);

		/*This if checks to see which way we want to push an object so that objects move in the 
		correct direction based on the deltaX and deltaY (we use > because we use negative numbers)*/
		if (intersectX > intersectY)
		{
			/*This will push objects away from one another in the X direction. The other.move is 
			negative to ensure that the objects push away from each other. If they push each other in the 
			same direction they will push one another endlessly*/
			if(deltaX > 0.0f)
			{
				Move(intersectX * (1.0f - push), 0.0f);
				other.Move(-intersectX * push, 0.0f);
			}
			else
			{
				Move(-intersectX * (1.0f - push), 0.0f);
				other.Move(intersectX * push, 0.0f);
			}
		}
		else 
		{	
			/*This will push objects away from one another in the Y direction*/
			if (deltaY > 0.0f)
			{
				Move(0.0f, intersectY * (1.0f - push));
				other.Move(0.0f, -intersectY * push);
			}
			else
			{
				Move(0.0f, -intersectY * (1.0f - push));
				other.Move(0.0f, intersectY * push);
			}
		}

		return true;
	}

	return false;
}

bool Collider::CheckProjCollision(Collider & other)
{
	sf::Vector2f otherPosition = other.GetPosition();
	sf::Vector2f otherHalfSize = other.GetHalfSize();
	sf::Vector2f thisPosition = GetPosition();
	sf::Vector2f thisHalfSize = GetHalfSize();

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;
	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);


	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		return true;
	}
	return false;
}

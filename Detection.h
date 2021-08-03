#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Random.h"

class Detection
{
public:
	Detection(sf::RectangleShape& body);
	~Detection();

	bool CheckDetection(Detection& other, float deltaTime, float _speed);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f; }
	void Move(float dx, float dy) { body.move(dx, dy); }

	bool GetDetect() { return detect; }

private:

	sf::RectangleShape& body;
	
	bool detect;
	float speed;
};


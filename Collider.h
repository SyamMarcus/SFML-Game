#pragma once
#include <SFML/Graphics.hpp>

class Collider
{
public:

	Collider(sf::RectangleShape& body);
	~Collider();


	/*This checks if an object is colliding with another and how much they will push one another*/
	bool CheckCollision(Collider& other, float push);

	bool CheckProjCollision(Collider& other);

	/*These are some functions to simplify the check collision code*/
	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f; }
	void Move(float dx, float dy) { body.move(dx, dy); }

private:

	sf::RectangleShape& body;

};


#include "Shotgun.h"



Shotgun::Shotgun(sf::Texture * texture) 
{
	shotTimer = 0;

	for(int i = 0; i < 5; i++)
		projectileVec.push_back(texture);
}
 
Shotgun::~Shotgun()
{
}

void Shotgun::Update(float deltaTime, sf::Vector2f _playerPos, sf::Vector2i _mousePos, sf::Vector2u _winSize)
{
	shotTimer += deltaTime;

	for (int i = 0; projectileVec.size(); i++)
	{
		//std::cout << "Update Shotgun bullet: " + i << std::endl;
		//Random signRan(1, 2);
		//Random spreadRan(10, 40);

		sf::Vector2i mousePos = _mousePos;

		if (i == 0)
		{
			//printf("1st\n");
			mousePos.x - 225;
			mousePos.y - 225;
		}

		if (i == 1)
		{
			//printf("2st\n");
			mousePos.x - 30;
			mousePos.y - 30;
		}

		if (i == 2)
		{
			mousePos.x - 10;
			mousePos.y - 10;
		}

		if (i == 3)
		{
			mousePos.x + 10;
			mousePos.y + 10;
		}

		if (i == 4)
		{
			mousePos.x + 30;
			mousePos.y + 30;
		}

		projectileVec[i].Update(deltaTime, _playerPos, mousePos, _winSize);

		shotTimer = 0.0f;
	}
		
}


void Shotgun::Draw(sf::RenderWindow & window)
{
	for (int i = 0; projectileVec.size(); i++)
	{
		//printf("boot\n");
		projectileVec[i].Draw(window);
	}
}

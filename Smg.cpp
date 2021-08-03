#include "smg.h"


Smg::Smg(sf::Texture * texture)
{
	eraseSet = false;
	projectileVec.push_back(texture);
}

Smg::~Smg()
{
}

void Smg::Update(float deltaTime, sf::Vector2f _playerPos, sf::Vector2i _mousePos, sf::Vector2u _winSize)
{
	sf::Vector2f playerPos = _playerPos;
	sf::Vector2i mousePos = _mousePos;
	sf::Vector2u winSize = _winSize;
	Random splatterChanceRan(1, 3);
	Random splatterTextureRan(1, 8);
	Random projSpreadRan(2, 25);
	Random projSpreadChanceRan(1, 2);
	for (size_t i = 0; i < projectileVec.size(); i++)
	{
		sf::Vector2i projMousePos;
		if (projSpreadChanceRan.GetRandNum() == 1)
		{
			projMousePos.x = mousePos.x + projSpreadRan.GetRandNum();
			projMousePos.y = mousePos.y + projSpreadRan.GetRandNum();
		}
		if (projSpreadChanceRan.GetRandNum() == 2)
		{
			projMousePos.x = mousePos.x - projSpreadRan.GetRandNum();
			projMousePos.y = mousePos.y - projSpreadRan.GetRandNum();
		}

		projectileVec[i].Update(deltaTime, playerPos, projMousePos, winSize);
		eraseSet = projectileVec[i].GetEraseSet();
	}
}


Collider Smg::GetCollider()
{
	for (size_t i = 0; i < projectileVec.size(); i++)
	{
		return Collider(projectileVec[i].GetCollider());
	}
}

sf::Vector2f Smg::GetPosition()
{
	for (size_t i = 0; i < projectileVec.size(); i++)
	{
		return sf::Vector2f(projectileVec[i].GetPosition());
	}
}

void Smg::Draw(sf::RenderWindow & window)
{
	for (size_t i = 0; i < projectileVec.size(); i++)
	{
		projectileVec[i].Draw(window);
	}
}
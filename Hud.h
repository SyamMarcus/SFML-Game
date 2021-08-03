#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>  
#include <string>  

class Hud
{
public:
	Hud(sf::Vector2f _viewCen);
	~Hud();
	
	void Update(sf::Vector2f _viewCen, sf::Vector2f _viewSize, int _health, int _totalHealth,
		bool _waveDowntime, int _currentWave, float _waveTimer, int _enemyCount, int _money);

	void gunUpdate(std::string weapon, int _ammoCount, int _ammoMagSize);

	void Draw(sf::RenderWindow& window);

private:
	sf::Vector2f viewCen;
	sf::Vector2f viewSize;
	bool waveDowntime;

	sf::Font font;
	sf::Text hudText;
	sf::Text ammoText;
	sf::Text waveText;
	sf::Text waveDowntimeText;
	sf::Text moneyText;
};


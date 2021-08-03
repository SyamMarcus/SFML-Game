#include "Hud.h"

Hud::Hud(sf::Vector2f _viewCen)
{
	if (!font.loadFromFile("Fonts/arial.ttf"))
		printf("FAILLED TO LOAD ARIAL\n");

	hudText.setFont(font);
	hudText.setCharacterSize(25);
	hudText.setFillColor(sf::Color::White);
	hudText.setOutlineColor(sf::Color::Black);
	hudText.setOutlineThickness(1);
	hudText.setString("Health: ");
	hudText.setPosition(0.0f, 0.0f);

	ammoText.setFont(font);
	ammoText.setCharacterSize(22);
	ammoText.setFillColor(sf::Color::White);
	ammoText.setOutlineColor(sf::Color::Black);
	ammoText.setOutlineThickness(1);
	ammoText.setString("Ammo: ");
	ammoText.setPosition(0.0f, 0.0f);

	waveText.setFont(font);
	waveText.setCharacterSize(22);
	waveText.setFillColor(sf::Color::White);
	waveText.setOutlineColor(sf::Color::Black);
	waveText.setOutlineThickness(1);
	waveText.setString("Wave: ");
	waveText.setPosition(0.0f, 0.0f);

	waveDowntimeText.setFont(font);
	waveDowntimeText.setCharacterSize(25);
	waveDowntimeText.setFillColor(sf::Color::White);
	waveDowntimeText.setOutlineColor(sf::Color::Black);
	waveDowntimeText.setOutlineThickness(1);
	waveDowntimeText.setString("Next Wave in :");
	waveDowntimeText.setPosition(0.0f, 0.0f);

	moneyText.setFont(font);
	moneyText.setCharacterSize(25);
	moneyText.setFillColor(sf::Color::White);
	moneyText.setOutlineColor(sf::Color::Black);
	moneyText.setOutlineThickness(1);
	moneyText.setString("Money: ");
	moneyText.setPosition(0.0f, 0.0f);
}

Hud::~Hud()
{
}

void Hud::Update(sf::Vector2f _viewCen, sf::Vector2f _viewSize, int _health, int _totalHealth, 
	bool _waveDowntime, int _currentWave, float _waveTimer, int _enemyCount, int _money)
{
	viewCen  = _viewCen;
	viewSize = _viewSize;

	//float width  = viewCen.x - (viewSize.x / 2);
	//float height = viewCen.y - (viewSize.y / 2);

	std::string health = std::to_string(_health);
	std::string totalHealth = std::to_string(_totalHealth);
	hudText.setString("Health: " + health + "/" + totalHealth);
	hudText.setPosition(viewCen.x - (viewSize.x / 2), viewCen.y - (viewSize.y / 2));

	std::string money = std::to_string(_money);
	moneyText.setString("Money: " + money);
	moneyText.setPosition(viewCen.x - (viewSize.x / 2), viewCen.y + (viewSize.y / 2.7));

	waveDowntime = _waveDowntime;
	if (waveDowntime)
	{
		int waveTimer = (int)_waveTimer;
		std::string waveCountdown = std::to_string(waveTimer + 1);
		waveDowntimeText.setString("Next Wave in : " + waveCountdown);
		waveDowntimeText.setPosition(viewCen.x - (viewSize.x / 2), viewCen.y + (viewSize.y / 2.3));
	}
	else
	{
		std::string enemyCount  = std::to_string(_enemyCount);
		std::string currentWave = std::to_string(_currentWave);
		waveText.setString("Wave: " + currentWave + " | Enemies Left: " + enemyCount);
		waveText.setPosition(viewCen.x - (viewSize.x / 2), viewCen.y + (viewSize.y / 2.3));
	}
	
}

void Hud::gunUpdate(std::string weapon, int _ammoCount, int _ammoMagSize)
{
	std::string ammo = std::to_string(_ammoCount);
	std::string ammoMagSize = std::to_string(_ammoMagSize);
	ammoText.setString(weapon + " Ammo: " + ammo + "/" + ammoMagSize);
	ammoText.setPosition(viewCen.x - (viewSize.x / 2), viewCen.y - (viewSize.y / 2.3));
}

void Hud::Draw(sf::RenderWindow & window)
{
	if (waveDowntime)
		window.draw(waveDowntimeText);
	else
		window.draw(waveText);

	window.draw(hudText);
	window.draw(ammoText); 
	window.draw(moneyText);
}

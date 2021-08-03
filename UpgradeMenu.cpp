#include "UpgradeMenu.h"


UpgradeMenu::UpgradeMenu(float _width, float _height)
{
	width = _width;
	height = _height;

	if (!font.loadFromFile("Fonts/arial.ttf"))
		printf("FAILLED TO LOAD ARIAL\n");

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Buy Pistol: £10");
	menu[0].setCharacterSize(25);
	menu[0].setPosition(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1);

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Buy Smg: £50");
    menu[1].setCharacterSize(25);
	menu[1].setPosition(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2);

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Buy Rpg: £120");
	menu[2].setCharacterSize(25);
	menu[2].setPosition(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3);

	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("Exit");
	menu[3].setCharacterSize(25);
	menu[3].setPosition(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 4);

	moneyText.setFont(font);
	moneyText.setCharacterSize(25);
	moneyText.setFillColor(sf::Color::White);
	moneyText.setOutlineColor(sf::Color::Black);
	moneyText.setOutlineThickness(1);
	moneyText.setString("Money: ");
	moneyText.setPosition(0.0f, 0.0f);

	selectedItemIndex = 0;
}

UpgradeMenu::~UpgradeMenu()
{
}

void UpgradeMenu::Update(sf::Vector2f _viewCen, int _money)
{
	sf::Vector2f viewCen = _viewCen;

	float width  = viewCen.x - 50;
	float height = viewCen.y;

	menu[0].setPosition(width, height - 150);
	menu[1].setPosition(width, height - 50);
	menu[2].setPosition(width, height + 50);
	menu[3].setPosition(width, height + 150);

	std::string money = std::to_string(_money);
	moneyText.setString("Money: " + money);
	moneyText.setPosition(width, height - 250);
}

void UpgradeMenu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void UpgradeMenu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void UpgradeMenu::Draw(sf::RenderWindow & window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
	window.draw(moneyText);
}

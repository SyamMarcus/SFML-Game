#include "Menu.h"



Menu::Menu(float _width, float _height)
{	
	width  = _width;
	height = _height;

	if (!font.loadFromFile("Fonts/arial.ttf"))
		printf("FAILLED TO LOAD ARIAL\n");

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Continue");
	menu[0].setPosition(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1);

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Options");
	menu[1].setPosition(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2);

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3);

	selectedItemIndex = 0;
}

Menu::~Menu()
{
}

void Menu::Update(sf::Vector2f _viewCen)
{
	sf::Vector2f viewCen = _viewCen;

	float width  = viewCen.x - 50;
	float height = viewCen.y;

	menu[0].setPosition(width, height - 100);
	menu[1].setPosition(width, height );
	menu[2].setPosition(width, height + 100);
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::Draw(sf::RenderWindow & window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

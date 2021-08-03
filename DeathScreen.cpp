#include "DeathScreen.h"



DeathScreen::DeathScreen(float _width, float _height)
{
	width = _width;
	height = _height;

	

	if (!font.loadFromFile("Fonts/arial.ttf"))
		printf("FAILLED TO LOAD ARIAL\n");

	//TEXT FOR SCORE/WAVE ?????

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("YOU HAVE DIED");
	menu[0].setPosition(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1);
	menu[0].setOutlineThickness(2);
	menu[0].setOutlineColor(sf::Color::Black);

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Press Enter To Exit");
	menu[1].setPosition(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2);
	menu[1].setOutlineThickness(2);
	menu[1].setOutlineColor(sf::Color::Black);
	
	alphaTimer = 0;
	alpha = 255;
	
	body.setPosition(width / 2, height / 2);
	body.setSize(sf::Vector2f(width, height));
	body.setOrigin(body.getSize() / 2.0f);
	body.setFillColor(sf::Color(200, 50, 50, alpha));
}

DeathScreen::~DeathScreen()
{
}

void DeathScreen::Update(sf::Vector2f _viewSize, float deltaTime) //BACKGROUND COLOUR RED TO CLEAR (BLACK BACKGROUND)
{
	alphaTimer += deltaTime;
	//std::cout << alphaTimer << std::endl;

	if (alphaTimer >= 0.03f && alpha >= 1)
	{
		alpha--;
		alphaTimer = 0.0f;
	}

	body.setFillColor(sf::Color(240, 115, 115, alpha));

	sf::Vector2f viewSize = _viewSize;

	float width = viewSize.x;
	float height = viewSize.y - 60;

	body.setPosition(width, height);

	menu[0].setPosition(width - 100, height);
	menu[1].setPosition(width - 100, height + 50);
}




void DeathScreen::Draw(sf::RenderWindow & window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);		
	}
	window.draw(body);
}

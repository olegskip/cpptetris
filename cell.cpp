#include "cell.h"

#include <random>
#include <time.h>

Cell::Cell(int x, int y, int sideSize, sf::Color color, sf::Vector2f pos): position(pos)
{
    activeColor = sf::Color(90, 180, 90);

	rectangleObj.setPosition(sf::Vector2f(x, y));
	rectangleObj.setSize(sf::Vector2f(sideSize, sideSize));
	rectangleObj.setFillColor(sf::Color::Transparent);
}

void Cell::draw(sf::RenderWindow &window)
{
	rectangleObj.setFillColor(activeColor);
	window.draw(rectangleObj);
}

void Cell::draw(sf::RenderWindow &window, sf::Color color)
{
	activeColor = color;
	rectangleObj.setFillColor(color);
	window.draw(rectangleObj);	
}

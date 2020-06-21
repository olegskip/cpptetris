#pragma once
#include <SFML/Graphics.hpp>
#include "config.h"


class Cell
{
public:
	Cell(int x, int y, int sideSize, sf::Vector2f pos);
	// Cell() {};
	
	void draw(sf::RenderWindow &window);
	void draw(sf::RenderWindow &window, sf::Color color);
	const sf::Vector2f position;
	sf::Color activeColor;

protected:
	sf::RectangleShape rectangleObj;
};

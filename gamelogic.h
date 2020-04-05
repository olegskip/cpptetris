#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <thread>

#include "cell.h"


class GameLogic
{
public:
	GameLogic();
	void updateTime();
	float getTime() const;

	void update();
	void moveLeft();
	void moveRight();
	void moveDown();
	void setBlockStatus();

	void spawnNewItem();

	void gameOver();
	void restart();
	bool togglePause();

	void draw(sf::RenderWindow &window);

private:
	sf::Clock clock;
	float time;
	std::vector<std::vector<std::shared_ptr<Cell>>> cells;
	std::vector<std::shared_ptr<Cell>> activeCells;
	std::vector<std::shared_ptr<Cell>> doneCells;

	std::thread updateThread = std::thread(&GameLogic::update, this);

	bool isGameOver = false;
	bool isPause = false;
	int currentBlockStatus = 0;
	int currentBlock;
	sf::Color currentColor;

	int getRandomInt(int from, int to);
	void checkIfRowFulled(int row);
	void moveDownTopCells(int row);
};
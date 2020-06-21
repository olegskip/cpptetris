#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <thread>

#include "cell.h"


enum BlocksTypes
{
	tBlock, oBlock, lBlock, jBlock, iBlock, zBlock, sBlock
};

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

	bool isGameOver = false;
	bool isPause = false;
	unsigned int currentBlockStatus = 0;
	BlocksTypes currentBlockType;
	std::unordered_map<BlocksTypes, std::vector<std::vector<sf::Vector2f>>> blocksSceletons;
	sf::Color currentColor;

	int getRandomInt(int from, int to);
	void checkIfRowFulled(int row);
	void moveDownTopCells(int row);
};
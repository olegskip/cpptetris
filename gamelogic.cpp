#include "gamelogic.h"

#include <random>
#include <time.h>

GameLogic::GameLogic()
{
	//init cells

	for(int x = 0; x < config::CELLS_COUNT.x; ++x) {
		cells.push_back(std::vector<std::shared_ptr<Cell>>());
		for(int y = 0; y < config::CELLS_COUNT.y; ++y) {
			cells[x].push_back(std::shared_ptr<Cell>(new Cell((x * 2) + (x * config::CELL_SISE), (y * 2) + (y * config::CELL_SISE), 
				config::CELL_SISE, sf::Color::Red, sf::Vector2f(x, y))));
		}
	}
	updateThread.detach();
	spawnNewItem();
}

void GameLogic::updateTime()
{
    time = clock.getElapsedTime().asMicroseconds();
	clock.restart();
	time = time / 800; // game speed
}

float GameLogic::getTime() const
{
	return time;
}

void GameLogic::update()
{
	while(true) {
		// check is spawn free
		moveDown();
		sf::sleep(sf::milliseconds(200));
	}
}

void GameLogic::moveLeft()
{
	if(isPause) return;
	std::list<sf::Vector2f> posList;
	for(auto &activeCell: activeCells)
		posList.push_back(activeCell->position);

	// check if near the border for not to let that leave of the game scene 
	for(auto pos: posList) {
		if(pos.x <= 0)
			return;
		// check if near another figure
		for(auto &doneCell: doneCells) {
			if(pos.x - 1 == doneCell->position.x && pos.y && pos.y == doneCell->position.y)
				return;
		}
	}
	activeCells.clear();

	for(auto pos: posList)
		activeCells.push_back(cells[pos.x - 1][pos.y]);
}

void GameLogic::moveRight()
{
	if(isPause) return;
	std::list<sf::Vector2f> posList;
	for(auto &activeCell: activeCells)
		posList.push_back(activeCell->position);
	
	for(auto pos: posList) {
		// check if near the border for not to let that leave of the game scene 
		if(pos.x >= cells.size() - 1)
			return;
		// check if near another figure
		for(auto &doneCell: doneCells) {
			if(pos.x + 1 == doneCell->position.x && pos.y && pos.y == doneCell->position.y)
				return;
		}
	}
	activeCells.clear();

	for(auto pos: posList)
		activeCells.push_back(cells[pos.x + 1][pos.y]);
}

void GameLogic::moveDown()
{
	if(isPause) return;
	for(auto &activeCell: activeCells) {
		for(auto &doneCell: doneCells) {
			if(activeCell->position.x == doneCell->position.x && activeCell->position.y + 1 == doneCell->position.y) {
				std::copy(activeCells.begin(), activeCells.end(), std::back_inserter(doneCells));
				activeCells.clear();
				spawnNewItem();
				break;
			}
		}
	}

	std::list<sf::Vector2f> posList;
	for(auto &activeCell: activeCells)
		posList.push_back(activeCell->position);

	activeCells.clear();

	for(auto pos: posList) {
		if(pos.y < cells[0].size() - 1)
			activeCells.push_back(cells[pos.x][pos.y + 1]);
		else {
			for(auto pos: posList)
				doneCells.push_back(cells[pos.x][pos.y]);
			activeCells.clear();
			spawnNewItem();
			break;
		}
	}

	checkIfRowFulled(cells[0].size());
}

void GameLogic::setBlockStatus()
{
	if(isPause) return;
	const int startBlockStatus = currentBlockStatus;
	if(++currentBlockStatus > config::blocks[static_cast<int>(currentBlock)].size() - 1)
		currentBlockStatus = 0;

	sf::Vector2f pos;
	pos = activeCells[0]->position;
	// check for not to let get out of the game scene a part of a figure
	for(auto cell: config::blocks[static_cast<int>(currentBlock)][currentBlockStatus]) {
		if(cell.x + pos.x < 0 || cell.x + pos.x >= cells.size() || cell.y + pos.y >= cells[0].size()) {
			currentBlockStatus = startBlockStatus;
			return;
		}
	}

	for(auto cell: config::blocks[static_cast<int>(currentBlock)][currentBlockStatus]) {
		for(auto &doneCell: doneCells) {
			if(cell.x + pos.x == doneCell->position.x && cell.y + pos.y == doneCell->position.y) {
				currentBlockStatus = startBlockStatus;
				return;
			}
		}
	}	

	activeCells.clear();
	for(auto cell: config::blocks[static_cast<int>(currentBlock)][currentBlockStatus])
		activeCells.push_back(cells[cell.x + pos.x][cell.y + pos.y]);
}

void GameLogic::spawnNewItem()
{ // drawing for the top left to the bottom right
	if(activeCells.size() > 0 || isGameOver || isPause) return;
	currentBlockStatus = 0;

	currentColor = config::CELL_COLORS[getRandomInt(0, config::CELL_COLORS.size() - 1)];
	int randomFigureIndex = getRandomInt(0, config::blocks.size() - 1);

	currentBlock = randomFigureIndex;
	for(auto cell: config::blocks[currentBlock].front())
		activeCells.push_back(cells[cell.x + config::SPAWN_POSITION.x][cell.y + config::SPAWN_POSITION.y]);

	// if the spawn is blocked
	for(auto &activeCell: activeCells) {
		for(auto &doneCell: doneCells) {
			if(activeCell->position == doneCell->position) {
				activeCells.clear();
				restart();
				return;
			}
		}
	}
}

void GameLogic::gameOver()
{
	std::copy(activeCells.begin(), activeCells.end(), std::back_inserter(doneCells));
	activeCells.clear();
	for(int y = 0; y < cells[0].size(); ++y) {
		for(int x = 0; x < cells.size(); ++x) {
			if(std::find(doneCells.begin(), doneCells.end(), cells[x][y]) == doneCells.end())
				cells[x][y]->activeColor = sf::Color::Transparent;
		}
	}

	const sf::Color randomColor = config::CELL_COLORS[getRandomInt(0, config::CELL_COLORS.size() - 1)];

	std::thread([=]{
		for(int y = 0; y < cells[0].size() / 2; ++y) {
			for(int x = 0; x < cells.size(); ++x) {
				cells[x][y]->activeColor = randomColor;
			}
			sf::sleep(sf::milliseconds(50));
		}
	}).detach();

	for(int y = cells[0].size() - 1; y >= cells[0].size() / 2; --y) {
		for(int x = 0; x < cells.size(); ++x) {
			cells[x][y]->activeColor = randomColor;
		}
		sf::sleep(sf::milliseconds(50));
	}
	
	sf::sleep(sf::milliseconds(200));
	for(int x = cells.size() - 1; x >= 0; --x) {	
		for(int y = cells[0].size() - 1; y >= 0; --y) 
			cells[x][y]->activeColor = sf::Color::Transparent;	
		sf::sleep(sf::milliseconds(50));
	}
	doneCells.clear();
	sf::sleep(sf::milliseconds(200));
	isGameOver = false;
	isPause = false;
	spawnNewItem();
}

void GameLogic::restart()
{
	if(isGameOver) return;
	isGameOver = true;
	isPause = false;
	std::thread([=]{gameOver();}).detach();	
}

bool GameLogic::togglePause()
{
	isPause = !isPause;
	return isPause;
}

void GameLogic::draw(sf::RenderWindow &window)
{
	// draw cells
	for(auto &cell: activeCells)
		cell->draw(window, currentColor);

	for(auto &cell: doneCells)
		cell->draw(window);
		
	if(isGameOver) {
		for(int x = 0; x < cells.size(); ++x) {
			for(int y = 0; y < cells[0].size(); ++y)
				cells[x][y]->draw(window);
		}
	}
}

int GameLogic::getRandomInt(int from, int to)
{
	std::random_device dev;
	std::mt19937 rng(dev());

	std::uniform_int_distribution<std::mt19937::result_type> randomDist(from, to);
	return randomDist(rng);
}

void GameLogic::checkIfRowFulled(int row)
{
	if(row <= 0) return;
	int rowCellsCount = 0;
	for(auto &doneCell: doneCells) {
		if(doneCell->position.y == cells[0].size() - 1)
			rowCellsCount++;
	}

	if(rowCellsCount == cells.size()) {
		for(int i = doneCells.size() - 1; i >= 0; --i) {
			if(doneCells[i]->position.y == cells[0].size() - 1) {
				doneCells.erase(doneCells.begin() + i);
			}
		}
		moveDownTopCells(cells[0].size());
	}
	checkIfRowFulled(row - 1);
}

void GameLogic::moveDownTopCells(int row)
{
	auto doneCellsTemp = doneCells;
	doneCells.clear();
	for(int y = row; y > 0; --y) {
		for(auto &cell: doneCellsTemp) {
			if(cell->position.y == y) {
				doneCells.push_back(cells[cell->position.x][cell->position.y + 1]);
				doneCells.back()->activeColor = cells[cell->position.x][cell->position.y + 1]->activeColor;
			}
		}
	}
}

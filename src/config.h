#pragma once
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <string>
#include <unordered_map>


namespace config
{
	const float START_SPEED = 0.2f;
	const int CELL_SISE = 25;
	const sf::Vector2f CELLS_COUNT = sf::Vector2f(20, 30);
	const int WINDOW_WIDTH = CELLS_COUNT.x * 27;
	const int WINDOW_HEIGHT = CELLS_COUNT.y * 27 + 5;

	const sf::Color BACKGROUND_COLOR = sf::Color(38, 38, 38);
	const std::vector<sf::Color> CELL_COLORS = {sf::Color(230, 235, 235), sf::Color(50, 150, 50), sf::Color(220, 35, 35),
											    sf::Color(80, 100, 220), sf::Color(250, 220, 70), sf::Color(20, 190, 160)};

	const sf::Vector2f SPAWN_POSITION = sf::Vector2f(CELLS_COUNT.x / 2 - 1, 5);

	const std::string ICON_PATH = "data/author.png";
	const std::string MAIN_FONT = "data/pixeboy.ttf";

	const sf::Color AUTHOR_TEXT_COLOR = sf::Color(210, 210, 220);

	// figures
	const std::vector<std::vector<sf::Vector2f>> tBlock = {
		std::vector<sf::Vector2f> {
			sf::Vector2f(0, 0), sf::Vector2f(1, -1), sf::Vector2f(1, 0), sf::Vector2f(2, 0)
		},
		std::vector<sf::Vector2f> {
			sf::Vector2f(1, -1), sf::Vector2f(1, 0), sf::Vector2f(1, 1), sf::Vector2f(2, 0)
		},
		std::vector<sf::Vector2f> {
			sf::Vector2f(-1, 1), sf::Vector2f(0, 1), sf::Vector2f(0, 2), sf::Vector2f(1, 1)
		},
		std::vector<sf::Vector2f> {
			sf::Vector2f(0, 0), sf::Vector2f(1, -1), sf::Vector2f(1, 0), sf::Vector2f(1, 1)
		}
	};
	const std::vector<std::vector<sf::Vector2f>> oBlock = {
		std::vector<sf::Vector2f> {
			sf::Vector2f(0, 0), sf::Vector2f(0, 1), sf::Vector2f(1, 0), sf::Vector2f(1, 1)
		}
	};
	const std::vector<std::vector<sf::Vector2f>> lBlock = {
		std::vector<sf::Vector2f> {
			sf::Vector2f(0, 1), sf::Vector2f(1, 1), sf::Vector2f(2, 0), sf::Vector2f(2, 1)
		},
		std::vector<sf::Vector2f> {
			sf::Vector2f(1, -1), sf::Vector2f(1, 0), sf::Vector2f(1, 1), sf::Vector2f(2, 1)
		},
		std::vector<sf::Vector2f> {
			sf::Vector2f(-1, 1), sf::Vector2f(-1, 2), sf::Vector2f(0, 1), sf::Vector2f(1, 1)
		},
		std::vector<sf::Vector2f> {
			sf::Vector2f(0, -1), sf::Vector2f(1, -1), sf::Vector2f(1, 0), sf::Vector2f(1, 1)
		}
	};
	const std::vector<std::vector<sf::Vector2f>> jBlock = {
		std::vector<sf::Vector2f> {
			sf::Vector2f(-1, 0), sf::Vector2f(-1, 1), sf::Vector2f(0, 1), sf::Vector2f(1, 1)
		},
		std::vector<sf::Vector2f> {
			sf::Vector2f(1, 0), sf::Vector2f(1, 1), sf::Vector2f(1, 2), sf::Vector2f(2, 0)
		},
		std::vector<sf::Vector2f> {
			sf::Vector2f(-1, 1), sf::Vector2f(0, 1), sf::Vector2f(1, 1), sf::Vector2f(1, 2)
		},
		std::vector<sf::Vector2f> {
			sf::Vector2f(1, -1), sf::Vector2f(1, 0), sf::Vector2f(0, 1), sf::Vector2f(1, 1)
		}
	};
	const std::vector<std::vector<sf::Vector2f>> iBlock = {
		std::vector<sf::Vector2f> {
			sf::Vector2f(-1, 1), sf::Vector2f(0, 1), sf::Vector2f(1, 1), sf::Vector2f(2, 1)
		},
		std::vector<sf::Vector2f> {
			sf::Vector2f(1, -1), sf::Vector2f(1, 0), sf::Vector2f(1, 1), sf::Vector2f(1, 2)
		}
	};
	const std::vector<std::vector<sf::Vector2f>> zBlock = {
		std::vector<sf::Vector2f> {
			sf::Vector2f(0, 0), sf::Vector2f(1, 0), sf::Vector2f(1, 1), sf::Vector2f(2, 1)
		},
		std::vector<sf::Vector2f> {
			sf::Vector2f(0, 0), sf::Vector2f(0, 1), sf::Vector2f(1, -1), sf::Vector2f(1, 0)
		}
	};
	const std::vector<std::vector<sf::Vector2f>> sBlock = {
		std::vector<sf::Vector2f> {
			sf::Vector2f(0, 2), sf::Vector2f(1, 1), sf::Vector2f(1, 2), sf::Vector2f(2, 1)
		},
		std::vector<sf::Vector2f> {
			sf::Vector2f(0, -2), sf::Vector2f(0, -1), sf::Vector2f(1, -1), sf::Vector2f(1, 0)
		}
	};
}
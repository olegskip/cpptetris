#include "gamelogic.h"
#include "config.h"


int main()
{
	GameLogic gameLogic;
	sf::RenderWindow window(sf::VideoMode(config::WINDOW_WIDTH, config::WINDOW_HEIGHT), "Skip");
	window.setFramerateLimit(60);


	sf::Image icon;
    if(!icon.loadFromFile(config::ICON_PATH))
		return EXIT_FAILURE;
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	sf::Font mainFont;
	if(!mainFont.loadFromFile(config::MAIN_FONT))
		return EXIT_FAILURE;

	sf::Text authorText;
	authorText.setString("Programmer: Oleg Skip\nDesigner: Zahar Sydoryk");
	authorText.setFont(mainFont);
	authorText.setCharacterSize(18);
	authorText.setFillColor(config::AUTHOR_TEXT_COLOR);
	authorText.setPosition(window.getSize().x - 195, 0);

	window.setKeyRepeatEnabled(false);
	
	while(window.isOpen()) {
		sf::Event event;

		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		
			if(event.type == sf::Event::KeyPressed) {
				if(event.key.code == sf::Keyboard::R)
					gameLogic.restart();

				if (event.key.code == sf::Keyboard::P)
					gameLogic.togglePause();

				if(event.key.code == sf::Keyboard::Left)
					gameLogic.moveLeft();

				if(event.key.code == sf::Keyboard::Down)
					gameLogic.moveDown();

				if(event.key.code == sf::Keyboard::Right)
					gameLogic.moveRight();

				if(event.key.code == sf::Keyboard::Up)
					gameLogic.setBlockStatus();
				}
		}
		gameLogic.updateTime();

		window.clear(config::BACKGROUND_COLOR);

		gameLogic.draw(window);
		window.draw(authorText);
		
		window.display();
	}

	return EXIT_SUCCESS;
}
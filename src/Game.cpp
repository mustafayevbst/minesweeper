#include "Game.h"

Game::Game(int size, int mines)
    : window_(sf::VideoMode(size * tileSize_, size * tileSize_), "Minesweeper"),
      board_(size, mines)
{
}

void Game::run()
{
    while (window_.isOpen())
    {
        processEvents();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window_.close();
                break;

            case sf::Event::MouseButtonPressed: {
                int x = event.mouseButton.x / tileSize_;
                int y = event.mouseButton.y / tileSize_;

                if (event.mouseButton.button == sf::Mouse::Button::Left) {
                    board_.reveal(x, y);
                } else if (event.mouseButton.button == sf::Mouse::Button::Right) {
                    board_.toggleFlag(x, y);
                }
                break;
            }

            default:
                break;
        }
    }
}



void Game::render() {
    window_.clear();
    board_.draw(window_);  // <-- замените render на draw
    window_.display();
}

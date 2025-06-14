#include "Game.h"

Game::Game(int width, int height, int mines)
    : window_(sf::VideoMode(width * tileSize_, height * tileSize_), "Minesweeper"),
      board_(width, height, mines),
      menu_(width * tileSize_, height * tileSize_),
      currentScreen(GameScreen::MainMenu)
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
        if (event.type == sf::Event::Closed)
            window_.close();

        if (currentScreen == GameScreen::MainMenu) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up)
                    menu_.moveUp();
                else if (event.key.code == sf::Keyboard::Down)
                    menu_.moveDown();
                else if (event.key.code == sf::Keyboard::Enter) {
                    int selected = menu_.getSelectedIndex();
                    if (selected == 0) { // Старт
                        board_ = Board(10, 10, 5); // можно позже динамически задавать параметры
                        currentScreen = GameScreen::Playing;
                    } else if (selected == 1) { // Выбор уровня
                        // пока можно оставить пустым
                    } else if (selected == 2) { // Выход
                        window_.close();
                    }
                }
            }
        }
        else if (currentScreen == GameScreen::Playing) {
            // старая обработка игры
            if (event.type == sf::Event::MouseButtonPressed) {
                int x = event.mouseButton.x / tileSize_;
                int y = event.mouseButton.y / tileSize_;

                if (event.mouseButton.button == sf::Mouse::Button::Left) {
                    board_.clickCell(x, y);
                } else if (event.mouseButton.button == sf::Mouse::Button::Right) {
                    board_.toggleFlag(x, y);
                }
            }
        }
    }
}




void Game::render() {
    window_.clear();
    if (currentScreen == GameScreen::MainMenu) {
        menu_.draw(window_);
    }
    else if (currentScreen == GameScreen::Playing) {
        board_.draw(window_);
    }
    window_.display();
}


#include <iostream>
#include "Game.h"

Game::Game(int width, int height, int mines) :
    window_(sf::VideoMode(width * tileSize_, height * tileSize_), "Minesweeper", sf::Style::Titlebar | sf::Style::Close),
    board_(width, height, mines, tileSize_),
    menu_(window_.getSize().x, window_.getSize().y, { L"Старт", L"Выбрать сложность"}),
    difficultyMenu_(window_.getSize().x, window_.getSize().y, { L"Простой", L"Средний", L"Сложный" }),
    currentScreen_(GameScreen::MainMenu),
    currentWidth_(width),
    currentHeight_(height),
    currentMines_(mines)
{
    window_.setFramerateLimit(60);
    if (!backgroundTexture_.loadFromFile("assets/background.png")) {
        std::cerr << "Failed to load background image\n";
        std::exit(1);
    }
    if (!simpleBgTexture_.loadFromFile("assets/simplebg.png")) {
        std::cerr << "Failed to load simplebg.png\n";
        std::exit(1);
    }
    simpleBgSprite_.setTexture(simpleBgTexture_);

    if (!mediumBgTexture_.loadFromFile("assets/mediumbg.png")) {
        std::cerr << "Failed to load mediumbg.png\n";
        std::exit(1);
    }
    mediumBgSprite_.setTexture(mediumBgTexture_);

    if (!hardBgTexture_.loadFromFile("assets/hardbg.png")) {
        std::cerr << "Failed to load hardbg.png\n";
        std::exit(1);
    }
    hardBgSprite_.setTexture(hardBgTexture_);

    backgroundSprite_.setTexture(backgroundTexture_);
}

void Game::run()
{
    while (window_.isOpen())
    {
        processEvents();
        render();
    }
}

void Game::startNewGame(int width, int height, int mines) {
    board_ = Board(width, height, mines, tileSize_);
    window_.create(sf::VideoMode(width * tileSize_, height * tileSize_), "Minesweeper", sf::Style::Titlebar | sf::Style::Close);
    currentWidth_ = width;
    currentHeight_ = height;
    currentMines_ = mines;
}

void Game::resetGame() {
    startNewGame(currentWidth_, currentHeight_, currentMines_);
}

void Game::processEvents() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed){
            window_.close();
        }

        if (currentScreen_ == GameScreen::MainMenu) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    menu_.moveUp();
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    menu_.moveDown();
                }
                else if (event.key.code == sf::Keyboard::Enter) {
                    int selected = menu_.getSelectedIndex();
                    if (selected == 0) {
                        startNewGame(10, 8, 10);
                        currentScreen_ = GameScreen::Playing;
                    } else if (selected == 1) {
                        currentScreen_ = GameScreen::DifficultyMenu;
                    } else if (selected == 2) {
                        window_.close();
                    }
                }
            }
        }
        else if (currentScreen_ == GameScreen::DifficultyMenu) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    difficultyMenu_.moveUp();
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    difficultyMenu_.moveDown();
                }
                else if (event.key.code == sf::Keyboard::Enter) {
                    int selected = difficultyMenu_.getSelectedIndex();

                    if (selected == 0) {
                        startNewGame(10, 8, 10);
                    }
                    
                    else if (selected == 1) {
                        startNewGame(16, 16, 40);
                    }

                    else {
                        startNewGame(30, 16, 99);
                    }

                    currentScreen_ = GameScreen::Playing;
                }
            }
        }
        else if (currentScreen_ == GameScreen::Playing) {
            if (event.type == sf::Event::MouseButtonPressed) {
                int x = event.mouseButton.x / tileSize_;
                int y = event.mouseButton.y / tileSize_;

                if (event.mouseButton.button == sf::Mouse::Left) {
                    board_.clickCell(x, y);
                }
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    board_.toggleFlag(x, y);
                }
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (board_.gameState == GameState::Won || board_.gameState == GameState::Lost) {
                    if (event.key.code == sf::Keyboard::Enter) {
                    resetGame();
                    }
                    else if (event.key.code == sf::Keyboard::Escape) {
                        window_.create(sf::VideoMode(480, 480), "Minesweeper", sf::Style::Titlebar | sf::Style::Close);
                        currentScreen_ = GameScreen::MainMenu;
                    }
                }
            }
        }
    }
}

void Game::render() {
    window_.clear();

    if (currentScreen_ == GameScreen::MainMenu){
        window_.draw(backgroundSprite_);
        menu_.draw(window_);
    }
    else if (currentScreen_ == GameScreen::DifficultyMenu) {
        int selected = difficultyMenu_.getSelectedIndex();
        if (selected == 0)
            window_.draw(simpleBgSprite_);
        else if (selected == 1)
            window_.draw(mediumBgSprite_);
        else if (selected == 2)
            window_.draw(hardBgSprite_);
        difficultyMenu_.draw(window_);
    }
    else if (currentScreen_ == GameScreen::Playing) {
        board_.draw(window_);
    }

    window_.display();
}

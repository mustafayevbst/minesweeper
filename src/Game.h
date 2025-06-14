#pragma once

#include "Board.h"
#include "Menu.h"
#include <SFML/Graphics.hpp>

enum class GameScreen {
    MainMenu,
    Playing,
    Exit
};

class Game {
public:
    Game(int sizeX, int sizeY, int minesCount);
    void run();

private:
    void processEvents();
    void update();
    void render();

    int tileSize_ = 32;
    Board board_;
    sf::RenderWindow window_;
    sf::Font font_;

    GameScreen currentScreen;
    Menu menu_;
};

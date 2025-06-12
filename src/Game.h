#pragma once
#include "Board.h"
#include <SFML/Graphics.hpp>

class Game {
public:
    Game(); // Добавьте, если нужен
    Game(int size, int mines);
    void run();

private:
    void processEvents();
    void update();
    void render();
    void loadAssets();
    void drawCell(int x, int y, sf::RenderWindow& window);

    int tileSize_ = 32;
    Board board_;
    sf::RenderWindow window_;
    sf::Font font_;
};

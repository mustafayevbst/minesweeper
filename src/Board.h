#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Board {
public:
    Board(int w, int h, int m = 10);
    void reveal(int x, int y);
    void toggleFlag(int x, int y);
    void draw(sf::RenderWindow& window) const;
    int getTileSize() const;

private:
    void revealEmpty(int x, int y);
    int countMines(int x, int y) const;
    void placeMine(int x, int y);

    int width;
    int height;
    int mines;
    int tileSize;
    std::vector<std::vector<char>> field;
    std::vector<std::vector<bool>> revealed;
    std::vector<std::vector<bool>> flagged;
    sf::Font font;
};

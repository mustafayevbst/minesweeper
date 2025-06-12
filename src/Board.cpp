#include "Board.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

Board::Board(int w, int h, int m) : width(w), height(h), mines(m), tileSize(32) {
    field = std::vector<std::vector<char>>(width, std::vector<char>(height, '.'));
    revealed = std::vector<std::vector<bool>>(width, std::vector<bool>(height, false));
    flagged = std::vector<std::vector<bool>>(width, std::vector<bool>(height, false));

    std::srand(std::time(nullptr));
    int placed = 0;
    while (placed < mines) {
        int x = std::rand() % width;
        int y = std::rand() % height;
        if (field[x][y] != '*') {
            field[x][y] = '*';
            placed++;
        }
    }

    if (!font.loadFromFile("assets/arial.ttf")) {
        std::cerr << "Font not found\n";
        std::exit(1);
    }
}

void Board::reveal(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height || revealed[x][y] || flagged[x][y])
        return;

    revealed[x][y] = true;
    if (field[x][y] == '*') return;

    int count = countMines(x, y);
    if (count == 0)
        revealEmpty(x, y);
    else
        field[x][y] = '0' + count;
}

void Board::revealEmpty(int x, int y) {
    for (int dx = -1; dx <= 1; dx++)
        for (int dy = -1; dy <= 1; dy++)
            reveal(x + dx, y + dy);
}

void Board::toggleFlag(int x, int y) {
    if (!revealed[x][y])
        flagged[x][y] = !flagged[x][y];
}

void Board::draw(sf::RenderWindow& window) const {
    sf::RectangleShape cell(sf::Vector2f(tileSize - 2, tileSize - 2));
    sf::Text text("", font, 18);
    text.setFillColor(sf::Color::Black);

    for (int i = 0; i < width; ++i)
        for (int j = 0; j < height; ++j) {
            cell.setPosition(i * tileSize, j * tileSize);
            if (revealed[i][j]) {
                if (field[i][j] == '*')
                    cell.setFillColor(sf::Color::Red);
                else {
                    cell.setFillColor(sf::Color::White);
                    int mines = countMines(i, j);
                    if (mines > 0) {
                        text.setString(std::to_string(mines));
                        text.setPosition(i * tileSize + 10, j * tileSize + 5);
                        window.draw(text);
                    }
                }
            } else {
                cell.setFillColor(flagged[i][j] ? sf::Color::Blue : sf::Color::Green);
            }
            window.draw(cell);
        }
}

int Board::getTileSize() const {
    return tileSize;
}

int Board::countMines(int x, int y) const {
    int count = 0;
    for (int dx = -1; dx <= 1; dx++)
        for (int dy = -1; dy <= 1; dy++) {
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < width && ny >= 0 && ny < height && field[nx][ny] == '*')
                count++;
        }
    return count;
}

void Board::placeMine(int x, int y) {
    field[x][y] = '*';
}

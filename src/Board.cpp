#include "Board.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "Game.h"

Board::Board(int w, int h, int m, int tilesize) : width(w), height(h), mines(m), tileSize(tilesize) {
    field = std::vector<std::vector<char>>(width, std::vector<char>(height, '.'));
    revealed = std::vector<std::vector<bool>>(width, std::vector<bool>(height, false));
    flagged = std::vector<std::vector<bool>>(width, std::vector<bool>(height, false));

    std::srand(std::time(nullptr));

    if (!font.loadFromFile("assets/ZingRust.ttf")) {
        std::cerr << "Font not found\n";
        std::exit(1);
    }

    if (!tilesTexture.loadFromFile("assets/tiles.jpg")) {
        std::cerr << "Failed to load tiles.jpg\n";
        std::exit(1);
    }
}

void Board::placeMines(int firstClickX, int firstClickY) {
    int placed = 0;
    while (placed < mines) {
        int x = std::rand() % width;
        int y = std::rand() % height;

        // Проверяем, что мина не в запрещенной зоне (первая клетка + соседи)
        if (field[x][y] != '*' && !isInSafeZone(x, y, firstClickX, firstClickY)) {
            field[x][y] = '*';
            placed++;
        }
    }
}

bool Board::isInSafeZone(int x, int y, int safeX, int safeY) const {
    return (std::abs(x - safeX) <= 1) && (std::abs(y - safeY) <= 1);
}

void Board::reveal(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height || revealed[x][y] || flagged[x][y]) {
        return;
    }

    revealed[x][y] = true;
    if (field[x][y] == '*'){
        return;
    }

    int count = countMines(x, y);
    if (count == 0) {
        revealEmpty(x, y);
    }
    else {
        field[x][y] = '0' + count;
    }
}

void Board::revealEmpty(int x, int y) {
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++){
            reveal(x + dx, y + dy);
        }
    }
}

void Board::toggleFlag(int x, int y) {
    if (!revealed[x][y]) {
        flagged[x][y] = !flagged[x][y];
        
        // проверяем победу после флага
        if (checkWin()) {
            gameState = GameState::Won;
            revealAll();
        }
    }
}

void Board::draw(sf::RenderWindow& window) const {
    sf::Sprite sprite;
    sprite.setTexture(tilesTexture);
    window.setFramerateLimit(60);
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            sprite.setPosition(i * tileSize, j * tileSize);

            if (revealed[i][j]) {
                if (field[i][j] == '*') {
                    sprite.setTextureRect(sf::IntRect(9 * tileSize, 0, tileSize, tileSize));
                } 
                else {
                    int count = countMines(i, j);
                    sprite.setTextureRect(sf::IntRect(count * tileSize, 0, tileSize, tileSize));
                }
            } 
            else {
                if (flagged[i][j]) {
                    sprite.setTextureRect(sf::IntRect(11 * tileSize, 0, tileSize, tileSize));
                } 
                else {
                    sprite.setTextureRect(sf::IntRect(10 * tileSize, 0, tileSize, tileSize));
                }
            }

            window.draw(sprite);
        }
    }

    auto drawCenteredText = [&](const std::string& message, unsigned int charSize, sf::Color color, float yOffset) {
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(charSize);
        text.setFillColor(color);
        text.setString(sf::String::fromUtf8(message.begin(), message.end()));

        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
        text.setPosition(width * tileSize / 2.f, height * tileSize / 2.f + yOffset);

        window.draw(text);
    };

    if (gameState == GameState::Lost) {
        drawCenteredText(u8"Вы проиграли!", 48, sf::Color::Red, -30.f);
        drawCenteredText(u8"Для ещё одной попытки нажмите Enter!", 16, sf::Color::White, 30.f);
        drawCenteredText(u8"Для выхода в гл. меню нажмите Escape!", 16, sf::Color::White, 90.f);
    }

    if (gameState == GameState::Won) {
        drawCenteredText(u8"Вы выиграли!", 48, sf::Color::Green, -30.f);
        drawCenteredText(u8"Для ещё одной попытки нажмите Enter!", 16, sf::Color::White, 30.f);
        drawCenteredText(u8"Для выхода в гл. меню нажмите Escape!", 16, sf::Color::White, 90.f);
    }

    
}

int Board::getTileSize() const {
    return tileSize;
}

int Board::countMines(int x, int y) const {
    int count = 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < width && ny >= 0 && ny < height && field[nx][ny] == '*'){
                count++;
            }
        }
    }
    return count;
}

void Board::placeMine(int x, int y) {
    field[x][y] = '*';
}

void Board::revealAll() {
    for (int i = 0; i < width; ++i){
        for (int j = 0; j < height; ++j){
            revealed[i][j] = true;
        }
    }
}

bool Board::checkWin() const {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            if (field[i][j] != '*' && !revealed[i][j]) {
                return false; 
            }
        }
    }
    return true; 
}

void Board::clickCell(int x, int y) {
    if (gameState != GameState::Playing) {
        return;  
    }

    if (firstClick) {
        placeMines(x, y);
        firstClick = false;
    }

    if (revealed[x][y] || flagged[x][y]){
        return;  
    }

    revealed[x][y] = true;

    if (field[x][y] == '*') {
        gameState = GameState::Lost;
        revealAll();
    } 
    else {
        int count = countMines(x, y);
        if (count == 0){
            revealEmpty(x, y);
        }
        else{
            field[x][y] = '0' + count;
        }
        
        if (checkWin()) {
            gameState = GameState::Won;
            revealAll();  
        }
    }
}
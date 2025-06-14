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

    if (!font.loadFromFile("assets/Zing Rust.ttf")) {
        std::cerr << "Font not found\n";
        std::exit(1);
    }

    // Загрузка текстуры tiles.jpg
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

        // Проверяем, что (x, y) не в запрещенной зоне (первая клетка + соседи)
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

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            sprite.setPosition(i * tileSize, j * tileSize);

            if (revealed[i][j]) {
                if (field[i][j] == '*') {
                    sprite.setTextureRect(sf::IntRect(9 * tileSize, 0, tileSize, tileSize));
                } else {
                    int count = countMines(i, j);
                    sprite.setTextureRect(sf::IntRect(count * tileSize, 0, tileSize, tileSize));
                }
            } else {
                if (flagged[i][j]) {
                    sprite.setTextureRect(sf::IntRect(11 * tileSize, 0, tileSize, tileSize));
                } else {
                    sprite.setTextureRect(sf::IntRect(10 * tileSize, 0, tileSize, tileSize));
                }
            }

            window.draw(sprite);
        }
    }

    if (gameState == GameState::Lost) {
        sf::Text text1, text2;
        text1.setFont(font);
        text2.setFont(font);

        std::string message1 = u8"Вы проиграли!";
        text1.setString(sf::String::fromUtf8(message1.begin(), message1.end()));
        std::string message2 = u8"Нажмите ENTER для ещё одной попытки";
        text2.setString(sf::String::fromUtf8(message2.begin(), message2.end()));

        // Выбираем читаемый размер
        text1.setCharacterSize(48);
        text2.setCharacterSize(18);

    // Цвета, например красный для первого и белый для второго
        text1.setFillColor(sf::Color::Black);
        text2.setFillColor(sf::Color::White);

    // Центрируем текст1 по середине окна (ширина*tileSize, высота*tileSize)
        sf::Vector2f center(width * tileSize / 2.f, height * tileSize / 2.f);

    // Вычисляем bounds для text1
        sf::FloatRect bounds1 = text1.getLocalBounds();
        text1.setOrigin(bounds1.left + bounds1.width / 2.f, bounds1.top + bounds1.height / 2.f);
        text1.setPosition(center.x, center.y - 30);  // чуть выше центра

    // Аналогично для text2, но чуть ниже text1
        sf::FloatRect bounds2 = text2.getLocalBounds();
        text2.setOrigin(bounds2.left + bounds2.width / 2.f, bounds2.top + bounds2.height / 2.f);
        text2.setPosition(center.x, center.y + 30);  // чуть ниже центра

        window.draw(text1);
        window.draw(text2);
    }
    if (gameState == GameState::Won) {
        sf::Text text1, text2;
        text1.setFont(font);
        text2.setFont(font);

        std::string message1 = u8"Вы выиграли!";
        text1.setString(sf::String::fromUtf8(message1.begin(), message1.end()));

        std::string message2 = u8"Для ещё одной\nпопытки нажмите Enter!";
        text2.setString(sf::String::fromUtf8(message2.begin(), message2.end()));

        text1.setCharacterSize(48);
        text2.setCharacterSize(24);

        text1.setFillColor(sf::Color::Green);
        text2.setFillColor(sf::Color::White);

        sf::Vector2f center(width * tileSize / 2.f, height * tileSize / 2.f);

        sf::FloatRect bounds1 = text1.getLocalBounds();
        text1.setOrigin(bounds1.left + bounds1.width / 2.f, bounds1.top + bounds1.height / 2.f);
        text1.setPosition(center.x, center.y - 30);

        sf::FloatRect bounds2 = text2.getLocalBounds();
        text2.setOrigin(bounds2.left + bounds2.width / 2.f, bounds2.top + bounds2.height / 2.f);
        text2.setPosition(center.x, center.y + 30);

        window.draw(text1);
        window.draw(text2);
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

void Board::revealAll() {
    for (int i = 0; i < width; ++i)
        for (int j = 0; j < height; ++j)
            revealed[i][j] = true;
}

bool Board::checkWin() const {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            if (field[i][j] != '*' && !revealed[i][j]) {
                return false; // есть еще не открытые пустые клетки
            }
        }
    }
    return true; // все пустые клетки открыты
}

void Board::clickCell(int x, int y) {
    if (gameState != GameState::Playing)
        return;  // Игра уже окончена
    if (firstClick) {
        placeMines(x, y);
        firstClick = false;
    }
    if (revealed[x][y] || flagged[x][y])
        return;  // Уже открыта или помечена флагом

    revealed[x][y] = true;

    if (field[x][y] == '*') {
        gameState = GameState::Lost;
        revealAll();
    } else {
        int count = countMines(x, y);
        if (count == 0)
            revealEmpty(x, y);
        else
            field[x][y] = '0' + count;

        // Проверяем победу
        if (checkWin()) {
            gameState = GameState::Won;
            revealAll();  // Показываем все клетки
        }
    }
}


#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum class GameState {
    Playing,
    Lost,
    Won
};
class Board {
public:
    Board(int w, int h, int m, int tilesize);
    void reveal(int x, int y);
    void toggleFlag(int x, int y);
    void draw(sf::RenderWindow& window) const;
    int getTileSize() const;
    void placeMine(int x, int y);
    GameState gameState = GameState::Playing;
    void clickCell(int x, int y);  // Метод для обработки клика
    bool checkWin() const;
private:
    int width, height, mines;
    std::vector<std::vector<char>> field;
    std::vector<std::vector<bool>> revealed;
    std::vector<std::vector<bool>> flagged;
    sf::Font font;

    int tileSize;

    // Добавьте сюда:
    sf::Texture tilesTexture;

    bool firstClick = true;
    void placeMines(int firstClickX, int firstClickY); 
    bool isInSafeZone(int x, int y, int safeX, int safeY) const;
    
    int countMines(int x, int y) const;
    void revealEmpty(int x, int y);
    GameState getGameState() const { return gameState; }
    void revealAll();
};

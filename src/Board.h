#pragma once
#include <vector>

enum class CellState { Hidden, Revealed, Flagged };
enum class GameState { Playing, Won, Lost };

/**
 * @brief Класс представляет минное поле.
 */
class Board {
public:
    Board(int size, int mines);
    void reset(int size, int mines);
    void reveal(int x, int y);
    void toggleFlag(int x, int y);
    int countMinesAround(int x, int y) const;
    bool isMine(int x, int y) const;
    CellState getCellState(int x, int y) const;
    char getCellValue(int x, int y) const;
    GameState getGameState() const;
    int getSize() const;
    int getRemainingFlags() const;

private:
    void placeMines();
    void revealRecursive(int x, int y);
    void checkWin();

    int size_;
    int mines_;
    int revealedCount_;
    GameState gameState_;
    std::vector<std::vector<char>> field_;
    std::vector<std::vector<CellState>> state_;
};

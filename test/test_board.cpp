#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Board.h"

// Тестируем конструктор и начальное состояние
TEST_CASE("Board initialization") {
    Board board(5, 5, 3, 32);
    CHECK(board.getTileSize() == 32);
    CHECK(board.gameState == GameState::Playing);
}

// Проверка, что первый клик не может привести ни к победе, ни к поражению
TEST_CASE("Safe zone check") {
    Board board(5, 5, 3, 32);
    board.clickCell(2, 2);

    CHECK(board.gameState != GameState::Lost);
    CHECK(board.checkWin() == false);
}

// Проверка подсчёта мин вокруг клетки
TEST_CASE("Count mines") {
    Board board(3, 3, 0, 32);
    board.placeMine(0, 0);
    board.placeMine(1, 0);
    board.placeMine(0, 1);

    CHECK(BoardTestFriend::countMines(board, 1, 1) == 3);
    CHECK(BoardTestFriend::countMines(board, 2, 2) == 0);
}

// Проверка поражения
TEST_CASE("Click mine loses game") {
    Board board(2, 2, 0, 32);
    board.placeMine(1, 1);

    BoardTestFriend::setFirstClick(board, false);
    board.clickCell(1, 1);
    CHECK(board.gameState == GameState::Lost);
}

// Проверка победы
TEST_CASE("Winning the game") {
    Board board(2, 2, 1, 32);
    board.placeMine(0, 0);
    BoardTestFriend::setFirstClick(board, false);

    board.clickCell(0, 1);
    board.clickCell(1, 0);
    board.clickCell(1, 1);

    CHECK(board.gameState == GameState::Won);
}

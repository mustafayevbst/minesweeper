#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Board.h"

// Тестируем конструктор и начальное состояние
TEST_CASE("Board initialization") {
    Board board(5, 5, 3, 32);
    CHECK(board.getTileSize() == 32);
    CHECK(board.gameState == GameState::Playing);
}

TEST_CASE("Safe zone check") {
    Board board(5, 5, 3, 32);
    board.clickCell(2, 2);

    // Проверяем, что клик не приводит к поражению
    CHECK(board.gameState != GameState::Lost);

    // Проверяем, что доска ещё не выиграна (если ты ожидаешь, что игра не закончена)
    CHECK(board.checkWin() == false);

    // Дополнительно: можно проверить, что в зоне 3x3 нет мин
    for (int x = 1; x <= 3; x++)
        for (int y = 1; y <= 3; y++) {
            // Проверяем, что эти клетки не мины (если есть метод для проверки)
            // Например:
            // CHECK(!board.isMine(x, y)); // если есть такой метод
        }
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

// Проверка установки и снятия флага
TEST_CASE("Toggle flags") {
    Board board(3, 3, 0, 32);
    board.toggleFlag(0, 0);
    // Внутренние данные private, но флаг должен переключаться
    // При повторном вызове флаг снимается (этот момент неявно)
    board.toggleFlag(0, 0);
}

// Проверка клика по мине и поражения
TEST_CASE("Click mine loses game") {
    Board board(3, 3, 0, 32);
    board.placeMine(1, 1);

    BoardTestFriend::setFirstClick(board, false); // Чтобы не переустанавливать мины
    board.clickCell(1, 1);
    CHECK(board.gameState == GameState::Lost);
}

// Проверка победы
TEST_CASE("Winning the game") {
    Board board(2, 2, 1, 32);
    board.placeMine(0, 0);
    BoardTestFriend::setFirstClick(board, false);

    // Открываем все клетки, кроме мины
    board.clickCell(0, 1);
    board.clickCell(1, 0);
    board.clickCell(1, 1);

    CHECK(board.gameState == GameState::Won);
}

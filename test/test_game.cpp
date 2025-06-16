#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Game.h"

// Чтобы собрать этот тест, в CMakeLists.txt надо добавить doctest, и 
// прописать запуск ctest после сборки.

TEST_CASE("Game initialization") {
    Game game(10, 8, 10);

    CHECK(game.currentWidth_ == 10);
    CHECK(game.currentHeight_ == 8);
    CHECK(game.currentMines_ == 10);
}

TEST_CASE("startNewGame sets correct parameters") {
    Game game(5, 5, 5);
    game.startNewGame(15, 12, 20);

    CHECK(game.currentWidth_ == 15);
    CHECK(game.currentHeight_ == 12);
    CHECK(game.currentMines_ == 20);
}

TEST_CASE("resetGame restarts with last parameters") {
    Game game(8, 8, 10);
    game.startNewGame(12, 12, 15);
    CHECK(game.currentWidth_ == 12);
    CHECK(game.currentHeight_ == 12);
    CHECK(game.currentMines_ == 15);

    game.resetGame();

    // После resetGame параметры должны остаться прежними
    CHECK(game.currentWidth_ == 12);
    CHECK(game.currentHeight_ == 12);
    CHECK(game.currentMines_ == 15);
}
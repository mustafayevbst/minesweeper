#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/Board.h"

TEST_CASE("Mine placement and counting") {
    Board b(5, 5, 0);
    b.placeMine(2, 2);
    CHECK(b.countMines(1, 1) == 1);
    CHECK(b.countMines(0, 0) == 0);
}

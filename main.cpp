#include "Game.h"

int main() {
    int width = 10;  // например, ширина поля
    int height = 10; // высота поля
    int mines = 5;  // число мин

    Game game(width, height, mines);
    game.run();

    return 0;
}

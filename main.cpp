#include "Game.h"

int main() {
    int width = 15;  // например, ширина поля
    int height = 15; // высота поля
    int mines = 0;  // число мин

    Game game(width, height, mines);
    game.run();

    return 0;
}

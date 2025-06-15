#pragma once

#include "Menu.h"
#include <SFML/Graphics.hpp>
#include "Board.h"


enum class GameScreen {
    MainMenu,
    DifficultyMenu,
    Playing,
    Exit
};

class Game {
public:
    Game(int sizeX, int sizeY, int minesCount);
    void run();
    int currentWidth_;
    int currentHeight_;
    int currentMines_;
    void resetGame();



private:
    void processEvents();
    void update();
    void render();
    void startNewGame(int width, int height, int mines);
    sf::Texture simpleBgTexture_;
    sf::Texture mediumBgTexture_;
    sf::Texture hardBgTexture_;

    sf::Sprite simpleBgSprite_;
    sf::Sprite mediumBgSprite_;
    sf::Sprite hardBgSprite_;


    int tileSize_ = 32;
    Board board_;
    sf::RenderWindow window_;
    sf::Font font_;
    sf::Texture backgroundTexture_;
    sf::Sprite backgroundSprite_;

    
    GameScreen currentScreen = GameScreen::MainMenu;  // <--- исправлено
    Menu difficultyMenu_;
    Menu menu_;
};

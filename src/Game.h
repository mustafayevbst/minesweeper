#pragma once

#include "Menu.h"
#include <SFML/Graphics.hpp>
#include "Board.h"

/**
 * @brief Перечисление экранов игры.
 */
enum class GameScreen {
    MainMenu,       ///< Главное меню
    DifficultyMenu, ///< Меню выбора сложности
    Playing,        ///< Игровой экран
    Exit            ///< Выход из игры
};

/**
 * @brief Класс управления основной логикой игры "Сапёр".
 * 
 * Отвечает за обработку событий, обновление состояния,
 * отрисовку, управление экранами и запуск самой игры.
 */
class Game {
public:
    /**
     * @brief Конструктор игры.
     * 
     * Инициализирует игру с параметрами поля.
     * 
     * @param sizeX Ширина поля в клетках.
     * @param sizeY Высота поля в клетках.
     * @param minesCount Количество мин на поле.
     */
    Game(int sizeX, int sizeY, int minesCount);

    /**
     * @brief Запустить игровой цикл.
     */
    void run();

    /// Текущая ширина игрового поля
    int currentWidth_;

    /// Текущая высота игрового поля
    int currentHeight_;

    /// Текущее количество мин на поле
    int currentMines_;

    /**
     * @brief Сбросить текущую игру к начальному состоянию.
     */
    void resetGame();

    /**
     * @brief Начать новую игру с указанными параметрами.
     * 
     * @param width Ширина поля в клетках.
     * @param height Высота поля в клетках.
     * @param mines Количество мин.
     */
    void startNewGame(int width, int height, int mines);

private:
    /**
     * @brief Обработать события ввода (клики, нажатия клавиш и т.п.).
     */
    void processEvents();

    /**
     * @brief Обновить состояние игры (логика игры).
     */
    void update();

    /**
     * @brief Отрисовать все элементы игры на экран.
     */
    void render();

    sf::Texture simpleBgTexture_;   ///< Текстура фона для легкого уровня
    sf::Texture mediumBgTexture_;   ///< Текстура фона для среднего уровня
    sf::Texture hardBgTexture_;     ///< Текстура фона для сложного уровня

    sf::Sprite simpleBgSprite_;     ///< Спрайт для простого фона
    sf::Sprite mediumBgSprite_;     ///< Спрайт для среднего фона
    sf::Sprite hardBgSprite_;       ///< Спрайт для сложного фона

    int tileSize_ = 32;             ///< Размер клетки в пикселях

    Board board_;                   ///< Игровая доска

    sf::RenderWindow window_;       ///< Окно игры SFML

    sf::Font font_;                 ///< Шрифт для текста

    sf::Texture backgroundTexture_; ///< Текущая текстура фона
    sf::Sprite backgroundSprite_;   ///< Текущий спрайт фона

    GameScreen currentScreen_ = GameScreen::MainMenu; ///< Текущий экран игры

    Menu difficultyMenu_;           ///< Меню выбора сложности
    Menu menu_;                    ///< Главное меню
};

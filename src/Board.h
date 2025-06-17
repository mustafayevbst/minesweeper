#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

/**
 * @brief Состояние игры.
 */
enum class GameState {
    Playing, ///< Игра продолжается
    Lost,    ///< Игрок проиграл
    Won      ///< Игрок выиграл
};

/**
 * @brief Класс, представляющий игровое поле "Сапёр".
 * 
 * Отвечает за хранение состояния поля, мин, флагов,
 * обработку кликов, проверку победы/поражения и отрисовку.
 */
class Board {
public:
    /**
     * @brief Конструктор доски.
     * 
     * @param w Ширина доски в клетках.
     * @param h Высота доски в клетках.
     * @param m Количество мин.
     * @param tilesize Размер одной клетки в пикселях.
     */
    Board(int w, int h, int m, int tilesize);

    /**
     * @brief Открыть клетку на доске (аналог клика).
     * 
     * @param x Координата клетки по оси X.
     * @param y Координата клетки по оси Y.
     */
    void reveal(int x, int y);

    /**
     * @brief Переключить флаг на клетке.
     * 
     * @param x Координата по X.
     * @param y Координата по Y.
     */
    void toggleFlag(int x, int y);

    /**
     * @brief Отрисовать игровое поле в окно.
     * 
     * @param window Ссылка на окно SFML для рисования.
     */
    void draw(sf::RenderWindow& window) const;

    /**
     * @brief Получить размер одной клетки.
     * 
     * @return Размер клетки в пикселях.
     */
    int getTileSize() const;

    /**
     * @brief Явно установить мину в указанную клетку.
     * Используется для тестирования.
     * 
     * @param x Координата по X.
     * @param y Координата по Y.
     */
    void placeMine(int x, int y);

    /**
     * @brief Посчитать количество мин вокруг клетки.
     * 
     * @param x Координата клетки по X.
     * @param y Координата клетки по Y.
     * @return Количество мин в соседних клетках.
     */
    int countMines(int x, int y) const;

    /**
     * @brief Обработать клик пользователя по клетке.
     * 
     * @param x Координата по X.
     * @param y Координата по Y.
     */
    void clickCell(int x, int y);

    /**
     * @brief Проверить, выиграна ли игра.
     * 
     * @return true, если все безопасные клетки открыты, иначе false.
     */
    bool checkWin() const;

    /// Текущее состояние игры
    GameState gameState = GameState::Playing;

    bool getFirstClick() const { return firstClick; }
    void setFirstClick(bool value) { firstClick = value; }

private:
    int width;   ///< Ширина доски в клетках
    int height;  ///< Высота доски в клетках
    int mines;   ///< Количество мин на поле

    std::vector<std::vector<char>> field;     ///< Игровое поле с минными и пустыми клетками
    std::vector<std::vector<bool>> revealed;  ///< Статус открытых клеток
    std::vector<std::vector<bool>> flagged;   ///< Статус флагов на клетках
    sf::Font font;                            ///< Шрифт для текста на клетках

    int tileSize; ///< Размер клетки в пикселях

    sf::Texture tilesTexture; ///< Текстура для отображения клеток

    bool firstClick = true; ///< Флаг первого клика, чтобы обеспечить безопасную зону

    /**
     * @brief Разместить мины на поле, кроме безопасной зоны.
     * 
     * @param firstClickX Координата X первого клика.
     * @param firstClickY Координата Y первого клика.
     */
    void placeMines(int firstClickX, int firstClickY);

    /**
     * @brief Проверить, входит ли клетка в безопасную зону вокруг первого клика.
     * 
     * @param x Координата клетки по X.
     * @param y Координата клетки по Y.
     * @param safeX Координата X первого клика.
     * @param safeY Координата Y первого клика.
     * @return true, если клетка в безопасной зоне, иначе false.
     */
    bool isInSafeZone(int x, int y, int safeX, int safeY) const;

    /**
     * @brief Рекурсивно открыть все пустые клетки вокруг.
     * 
     * @param x Координата клетки по X.
     * @param y Координата клетки по Y.
     */
    void revealEmpty(int x, int y);

    /**
     * @brief Получить текущее состояние игры.
     * 
     * @return Состояние игры (Playing, Won, Lost).
     */
    GameState getGameState() const { return gameState; }

    /**
     * @brief Открыть все клетки на поле (например, при проигрыше).
     */
    void revealAll();

    /// Дружественный класс-обёртка для доступа к приватным членам для тестирования
    friend class BoardTestFriend;
};
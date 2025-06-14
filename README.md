<h1>Руководство пользователя: Игра "Сапёр"</h1>

<h2>Назначение программы</h2>
<p>
Данное приложение представляет собой реализацию классической игры "Сапёр" на языке C++ с использованием графической библиотеки <strong>SFML</strong>. Игра позволяет пользователю тренировать внимание, логику и скорость принятия решений, открывая клетки игрового поля и избегая мин.
</p>

<h2>Функционал программы</h2>
<ul>
    <li>Графический интерфейс с использованием SFML</li>
    <li>Выбор уровня сложности</li>
    <li>Система победы и поражения</li>
    <li>Главное меню с навигацией</li>
    <li>Модульное тестирование (Doctest)</li>
    <li>Автоматическая генерация документации (Doxygen)</li>
    <li>Кроссплатформенная сборка через CMake</li>
</ul>

<h2>Установка программы</h2>

<h3>Предварительные требования</h3>
<ul>
    <li>Компилятор C++ с поддержкой стандарта <strong>C++17</strong></li>
    <li><strong>MinGW 13.1.0 (64-bit)</strong> — обязательная версия для Windows</li>
    <li><a href="https://github.com/brechtsanders/winlibs_mingw/releases/download/13.1.0-16.0.5-11.0.0-msvcrt-r5/winlibs-x86_64-posix-seh-gcc-13.1.0-mingw-w64msvcrt-11.0.0-r5.7z" target="_blank">Скачать MinGW 13.1.0</a></li>
    <li><strong>CMake</strong> версии 3.10 и выше</li>
    <li><strong>SFML 2.6.2 (64-bit)</strong></li>
    <li><a href="https://www.sfml-dev.org/files/SFML-2.6.2-windows-gcc-13.1.0-mingw-64-bit.zip" target="_blank">SFML 2.6.2 (64-bit)</a></li>
    <li>Doctest (для модульных тестов)</li>
    <li>Doxygen (для генерации документации)</li>
</ul>

<h3>Клонирование репозитория</h3>
<pre><code>git clone https://github.com/mustafayevbst/minesweeper.git
cd minesweeper</code></pre>

<h2>Сборка проекта</h2>

<ol>
    <li>Создайте директорию для сборки:</li>
</ol>
<pre><code>mkdir build
cd build</code></pre>

<ol start="2">
    <li>Запустите CMake:</li>
</ol>
<pre><code>cmake ..</code></pre>

<ol start="3">
    <li>Соберите проект:</li>
</ol>
<pre><code>cmake --build .</code></pre>

<h2>Запуск программы</h2>
<p>После сборки запустите исполняемый файл:</p>
<pre><code>./minesweeper.exe</code></pre>

<h2>Основные сценарии использования</h2>

<h3>Главное меню</h3>
<p>После запуска игры появляется главное меню с тремя пунктами:</p>
<ul>
    <li><strong>Старт</strong> — начать игру;</li>
    <li><strong>Выбрать уровень сложности</strong> — выбрать размер поля и количество мин;</li>
    <li><strong>Выход</strong> — завершить работу программы.</li>
</ul>

<img src="images/main_menu.png" alt="Главное меню">

<h3>Игровое поле</h3>
<p>После выбора уровня сложности создаётся игровое поле. Игрок должен открывать клетки, избегая мин:</p>

<img src="images/gameplay.png" alt="Игровое поле">

<h3>Победа</h3>
<p>Игра завершается победой, если все клетки без мин открыты:</p>
<img src="images/victory.png" alt="Победа">

<h3>Поражение</h3>
<p>Игра завершается поражением при открытии клетки с миной:</p>
<img src="images/defeat.png" alt="Поражение">

<h2>Пример кода (модуль Board)</h2>

<pre><code>// Board.h
class Board {
public:
    Board(int width, int height, int mines);
    void revealCell(int x, int y);
    bool isGameOver() const;
    bool isWin() const;
private:
    int width_;
    int height_;
    int mines_;
    // Остальные внутренние данные
};
</code></pre>

<h2>Генерация документации</h2>

<p>Чтобы сгенерировать документацию с помощью Doxygen:</p>

<pre><code>doxygen Doxyfile</code></pre>

<h2>Запуск модульных тестов</h2>

<p>Запуск тестов осуществляется отдельной сборкой и запуском тестового проекта:</p>

<pre><code>./tests/test_board.exe</code></pre>

<h2>Автор</h2>
<p><strong>mustafayevbst</strong></p>

</body>
</html>

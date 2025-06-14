Сапёр
Реализация классической игры «Сапёр» на языке C++ с использованием библиотеки SFML.

Особенности
Игровое поле разного размера и сложности

Главное меню

Поддержка графики с помощью SFML

Кроссплатформенная сборка через CMake

Поддержка тестов через Doctest

Генерация документации через Doxygen

Установка и сборка
Клонирование репозитория
bash
Копировать
Редактировать
git clone https://github.com/mustafayevbst/minesweeper.git
cd minesweeper
Необходимые зависимости
?? ВНИМАНИЕ: установленная версия MinGW должна быть строго 13.1.0 (64-bit)

MinGW 13.1.0 (64-bit)
Скачать можно отсюда:
https://github.com/brechtsanders/winlibs_mingw/releases/download/13.1.0-16.0.5-11.0.0-msvcrt-r5/winlibs-x86_64-posix-seh-gcc-13.1.0-mingw-w64msvcrt-11.0.0-r5.7z

Остальные зависимости:
C++ компилятор с поддержкой C++17

CMake 3.10+

SFML 2.6.2 (скачать: https://www.sfml-dev.org/download.php)

Doctest (для модульных тестов)

Doxygen (для генерации документации)

Сборка проекта
bash
Копировать
Редактировать
mkdir build
cd build
cmake ..
cmake --build .
Запуск
После сборки можно запустить исполняемый файл:

bash
Копировать
Редактировать
./minesweeper.exe
Структура проекта
bash
Копировать
Редактировать
minesweeper/
?
??? src/
?   ??? Board.h / Board.cpp
?   ??? Game.h / Game.cpp
?   ??? Menu.h / Menu.cpp
?   ??? ... (остальные исходники)
?
??? assets/
?   ??? (ресурсы игры: шрифты, текстуры)
?
??? tests/
?   ??? (модульные тесты на doctest)
?
??? docs/
?   ??? (документация, генерируемая Doxygen)
?
??? CMakeLists.txt
??? README.md
Автор
mustafayevbst
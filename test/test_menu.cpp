#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Menu.h"
#include <vector>

TEST_CASE("Menu initialization") {
    std::vector<std::wstring> labels = {L"Старт", L"Выбрать сложность", L"Выйти"};
    Menu menu(800, 600, labels);

    CHECK(menu.getSelectedIndex() == 0);
}

TEST_CASE("Menu moveDown changes selected index") {
    std::vector<std::wstring> labels = {L"Старт", L"Выбрать сложность", L"Выйти"};
    Menu menu(800, 600, labels);

    menu.moveDown();
    CHECK(menu.getSelectedIndex() == 1);

    menu.moveDown();
    CHECK(menu.getSelectedIndex() == 2);

    // Должен остаться на последнем элементе
    menu.moveDown();
    CHECK(menu.getSelectedIndex() == 2);
}

TEST_CASE("Menu moveUp changes selected index") {
    std::vector<std::wstring> labels = {L"Старт", L"Выбрать сложность", L"Выйти"};
    Menu menu(800, 600, labels);

    // Переместимся вниз, чтобы можно было двигать вверх
    menu.moveDown();
    menu.moveDown();
    CHECK(menu.getSelectedIndex() == 2);

    menu.moveUp();
    CHECK(menu.getSelectedIndex() == 1);

    menu.moveUp();
    CHECK(menu.getSelectedIndex() == 0);

    // Должен остаться на первом элементе
    menu.moveUp();
    CHECK(menu.getSelectedIndex() == 0);
}

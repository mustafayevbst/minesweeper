#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height) 
{
    if (!font.loadFromFile("assets/arial.ttf")) 
    {
        std::cerr << "Font not found\n";
        std::exit(EXIT_FAILURE);
    }

    std::vector<std::wstring> labels = {
        L"Старт",
        L"Выбрать сложность",
        L"Выйти"
    };

    for (size_t i = 0; i < labels.size(); ++i) {
    sf::Text text;
    text.setFont(font);
    text.setString(sf::String(labels[i]));
    text.setCharacterSize(40);
    text.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);

    // Получаем ширину текста
    sf::FloatRect textRect = text.getLocalBounds();

    // Ставим позицию по центру экрана с учётом ширины текста
    text.setPosition(
        width / 2.f - textRect.width / 2.f,
        height / 2.f - 60.f + i * 60.f
    );

    menuItems.push_back(text);

    std::wcout << L"Loaded menu item: " << labels[i] << std::endl;
}

    selectedIndex = 0;
}



void Menu::draw(sf::RenderWindow& window) {
    for (const auto& item : menuItems) {
        window.draw(item);
    }
}

void Menu::moveUp() {
    if (selectedIndex > 0) {
        menuItems[selectedIndex].setFillColor(sf::Color::White);
        selectedIndex--;
        menuItems[selectedIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::moveDown() {
    if (selectedIndex < menuItems.size() - 1) {
        menuItems[selectedIndex].setFillColor(sf::Color::White);
        selectedIndex++;
        menuItems[selectedIndex].setFillColor(sf::Color::Red);
    }
}

int Menu::getSelectedIndex() const {
    return selectedIndex;
}

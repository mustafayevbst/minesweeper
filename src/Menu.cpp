#include "Menu.h"

Menu::Menu(float width, float height) {
    if (!font.loadFromFile("assets/Zing Rust.ttf")) {
        // Обработать ошибку
    }

    std::vector<std::string> labels = {"Начать", "Выбрать сложность", "Выйти"};
    for (int i = 0; i < labels.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(labels[i]);
        text.setCharacterSize(40);
        text.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
        text.setPosition(width / 2 - 100, height / 2 - 60 + i * 60);
        menuItems.push_back(text);
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

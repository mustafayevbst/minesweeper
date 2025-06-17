#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height, const std::vector<std::wstring>& labels)
{
    if (!font.loadFromFile("assets/ZingRust.ttf")) {
        std::cerr << "Font not found\n";
        std::exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < labels.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(sf::String(labels[i]));
        text.setCharacterSize(40);
        text.setFillColor(i == 0 ? sf::Color::Red : sf::Color::Blue);

        sf::FloatRect textRect = text.getLocalBounds();

        text.setPosition(
            width / 2.f - textRect.width / 2.f,
            height / 2.f - 60.f + i * 60.f
        );

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
        menuItems[selectedIndex].setFillColor(sf::Color::Blue);
        selectedIndex--;
        menuItems[selectedIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::moveDown() {
    if (selectedIndex < menuItems.size() - 1) {
        menuItems[selectedIndex].setFillColor(sf::Color::Blue);
        selectedIndex++;
        menuItems[selectedIndex].setFillColor(sf::Color::Red);
    }
}

int Menu::getSelectedIndex() const {
    return selectedIndex;
}
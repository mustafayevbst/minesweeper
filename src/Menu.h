#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
public:
    Menu(float width, float height, const std::vector<std::wstring>& labels);
    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedIndex() const;
private:
    int selectedIndex;
    sf::Font font;
    std::vector<sf::Text> menuItems;
};

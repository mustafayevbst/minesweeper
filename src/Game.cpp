Game::Game() : window_(sf::VideoMode(640, 640, 32), "Minesweeper"), board_(10, 10, 15) {}

void Game::run() {
    while (window_.isOpen()) {
        sf::Event event;
        while (window_.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window_.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                int x = event.mouseButton.x / board_.getTileSize();
                int y = event.mouseButton.y / board_.getTileSize();
                if (event.mouseButton.button == sf::Mouse::Button::Left)
                    board_.reveal(x, y);
                else if (event.mouseButton.button == sf::Mouse::Button::Right)
                    board_.toggleFlag(x, y);
            }
        }
        render();
    }
}

void Game::render() {
    window_.clear(sf::Color::White);
    board_.draw(window_);
    window_.display();
}

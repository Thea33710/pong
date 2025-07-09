// menu.hpp
#pragma once
#include <SFML/Graphics.hpp>

enum class GameState {
    Menu,
    Playing,
    Options,
    Exit
};

class Menu {
public:
    Menu(sf::Font& font, unsigned int windowWidth);

    void draw(sf::RenderWindow& window);
    void handleClick(const sf::Vector2f& mousePos, GameState& state);

private:
    sf::Text title;
    sf::Text playButton;
    sf::Text optionsButton;
    sf::Text quitButton;
};

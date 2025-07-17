#pragma once
#include <SFML/Graphics.hpp>
#include "button.hpp"
#include "gamesettings.hpp"

class OptionsMenu {
public:
    OptionsMenu(const sf::Font& font, sf::Vector2u windowSize, GameSettings& settings);

    void update(const sf::Vector2f& mousePos);
    void draw(sf::RenderWindow& window);
    void handleClick(const sf::Event& event, const sf::Vector2f& mousePos);

    bool wantsToReturn() const;

private:
    sf::Text titre;
    std::vector<Button> boutons;
    GameSettings& settings;
    bool retourVersMenu = false;

    void setupMenu(sf::Vector2u windowSize, const sf::Font& font);
};

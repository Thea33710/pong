#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "gamestate.hpp"  // Si tu as défini GameState ailleurs

class Menu {
public:
   Menu(const sf::Font& font, unsigned int width);
    void draw(sf::RenderWindow& window);
    void handleClick(const sf::Vector2f& mousePos, GameState& state);
    void centerMenu(float screenWidth, float screenHeight);

private:
    sf::Text titre;
    std::vector<sf::Text> boutons;
};

#endif

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include "button.hpp"
#include "gamestate.hpp"

class Menu {
public:
    Menu(const sf::Font& font, float screenWidth, float screenHeight);
    void draw(sf::RenderWindow& window);
    void update(const sf::Vector2f& mousePos);
    void handleClick(const sf::Event& event, const sf::Vector2f& mousePos, GameState& state);


private:
    sf::Text titre;
    std::vector<Button> boutons;
    void centerMenu(float screenWidth, float screenHeight);

    sf::SoundBuffer clickBuffer;
    sf::Sound clickSound;
};

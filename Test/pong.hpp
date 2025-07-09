#pragma once
#include <SFML/Graphics.hpp>

class Pong {
public:
    Pong(sf::Font& font, sf::Vector2u windowSize);
    void reset(sf::Vector2u windowSize);
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

private:
    sf::RectangleShape leftPaddle;
    sf::RectangleShape rightPaddle;
    sf::CircleShape ball;
    sf::Vector2f ballVelocity;

    int scoreLeft;
    int scoreRight;

    sf::Text scoreText;
    int margin; // ← Ajouté ici

    void handleCollisions(sf::RenderWindow& window);
    void handleControls(sf::Vector2u size);
};

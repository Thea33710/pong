#ifndef PONG_HPP
#define PONG_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Pong {
public:
   Pong(const sf::Font& font, sf::Vector2u size);

    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void reset(sf::Vector2u windowSize);
    bool joueurAGagne() const;
    void drawDashedLine(sf::RenderWindow& window);

private:
    sf::RectangleShape raquetteGauche;
    sf::RectangleShape raquetteDroite;
    sf::CircleShape balle;

    sf::Text scoreText;
    int scoreGauche = 0;
    int scoreDroite = 0;
    const int SCORE_MAX = 5;

    sf::Vector2f balleVitesse;

    sf::SoundBuffer bounceBuffer;
    sf::Sound bounceSound;
};

#endif

#include "pong.hpp"
#include <sstream>

Pong::Pong(const sf::Font& font, sf::Vector2u windowSize) {
    // Raquettes
    raquetteGauche.setSize({ 10.f, 100.f });
    raquetteGauche.setFillColor(sf::Color::White);
    raquetteGauche.setPosition(30.f, windowSize.y / 2.f - 50.f);

    raquetteDroite.setSize({ 10.f, 100.f });
    raquetteDroite.setFillColor(sf::Color::White);
    raquetteDroite.setPosition(windowSize.x - 40.f, windowSize.y / 2.f - 50.f);

    // Balle
    balle.setRadius(10.f);
    balle.setFillColor(sf::Color::White);
    balle.setOrigin(10.f, 10.f);
    balle.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
    balleVitesse = { -5.f, -5.f };

    // Score
    scoreText.setFont(font);
    scoreText.setCharacterSize(36);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(windowSize.x / 2.f - 50.f, 20.f);
}

void Pong::update(sf::RenderWindow& window) {
    // Déplacement balle
    balle.move(balleVitesse);

    // Rebonds haut/bas
    if (balle.getPosition().y < 0 || balle.getPosition().y > window.getSize().y)
        balleVitesse.y *= -1;

    // Rebonds raquettes
    if (balle.getGlobalBounds().intersects(raquetteGauche.getGlobalBounds()) ||
        balle.getGlobalBounds().intersects(raquetteDroite.getGlobalBounds())) {
        balleVitesse.x *= -1;
    }

    // Marquer un point
    if (balle.getPosition().x < 0) {
        scoreDroite++;
        balle.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
    } else if (balle.getPosition().x > window.getSize().x) {
        scoreGauche++;
        balle.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
    }

    // Contrôles raquette gauche (W/S)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        raquetteGauche.move(0.f, -5.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        raquetteGauche.move(0.f, 5.f);

    // Contrôles raquette droite (↑/↓)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        raquetteDroite.move(0.f, -5.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        raquetteDroite.move(0.f, 5.f);

    // Mise à jour du texte
    std::ostringstream ss;
    ss << scoreGauche << " : " << scoreDroite;
    scoreText.setString(ss.str());
}

void Pong::draw(sf::RenderWindow& window) {
    window.draw(raquetteGauche);
    window.draw(raquetteDroite);
    window.draw(balle);
    window.draw(scoreText);
}

void Pong::reset(sf::Vector2u windowSize) {
    scoreGauche = 0;
    scoreDroite = 0;

    raquetteGauche.setPosition(30.f, windowSize.y / 2.f - 50.f);
    raquetteDroite.setPosition(windowSize.x - 40.f, windowSize.y / 2.f - 50.f);
    balle.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
    balleVitesse = { -5.f, -5.f };
}

bool Pong::joueurAGagne() const {
    return scoreGauche >= SCORE_MAX || scoreDroite >= SCORE_MAX;
}

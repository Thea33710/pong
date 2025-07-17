#include "pong.hpp"
#include <sstream>
#include <iostream>

Pong::Pong(const sf::Font& font, sf::Vector2u windowSize) {

    if (!bounceBuffer.loadFromFile("bounce.wav")) {
    std::cerr << "Erreur : impossible de charger bounce.wav\n";
} else {
    bounceSound.setBuffer(bounceBuffer);
    bounceSound.setVolume(100.f);  // Optionnel : volume entre 0 et 100
}

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
    scoreGauche = 0;
    scoreDroite = 0;
    scoreText.setFont(font);
    scoreText.setCharacterSize(36);
    scoreText.setFillColor(sf::Color::White);
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
        bounceSound.play();
    }

    // Marquer un point
    if (balle.getPosition().x < 0) {
        scoreDroite++;
        balle.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
    } else if (balle.getPosition().x > window.getSize().x) {
        scoreGauche++;
        balle.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
    }

    // Contrôles raquette gauche (Z/S)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        raquetteGauche.move(0.f, -5.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        raquetteGauche.move(0.f, 5.f);

     // Limiter raquette gauche dans la fenêtre
    if (raquetteGauche.getPosition().y < 0)
        raquetteGauche.setPosition(raquetteGauche.getPosition().x, 0);
    if (raquetteGauche.getPosition().y + raquetteGauche.getSize().y > window.getSize().y)
        raquetteGauche.setPosition(raquetteGauche.getPosition().x, window.getSize().y - raquetteGauche.getSize().y);

    // Contrôles raquette droite (↑/↓)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        raquetteDroite.move(0.f, -5.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        raquetteDroite.move(0.f, 5.f);

     // Limiter raquette droite dans la fenêtre
    if (raquetteDroite.getPosition().y < 0)
        raquetteDroite.setPosition(raquetteDroite.getPosition().x, 0);
    if (raquetteDroite.getPosition().y + raquetteDroite.getSize().y > window.getSize().y)
        raquetteDroite.setPosition(raquetteDroite.getPosition().x, window.getSize().y - raquetteDroite.getSize().y);

    // Mise à jour du texte
    std::ostringstream ss;
    ss << scoreGauche << " : " << scoreDroite;
    scoreText.setString(ss.str());

    // Recentrage horizontal du score en haut
    sf::FloatRect bounds = scoreText.getLocalBounds();
    scoreText.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    scoreText.setPosition(window.getSize().x / 2.f, 20.f + bounds.height / 2.f);
}

void Pong::draw(sf::RenderWindow& window) {
    drawDashedLine(window);
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

void Pong::drawDashedLine(sf::RenderWindow& window) {
    float dashHeight = 10.f;
    float gap = 10.f;
    float centerX = window.getSize().x / 2.f;

    // On calcule la hauteur du score (plus marge)
    float scoreHeight = scoreText.getLocalBounds().height + 40.f; // 40 px de marge sous le score

    sf::RectangleShape dash(sf::Vector2f(2.f, dashHeight));
    dash.setFillColor(sf::Color::White);

    for (float y = 0; y < window.getSize().y; y += dashHeight + gap) {
        // On saute les dash dans la zone du score
        if (y > scoreHeight) {
            dash.setPosition(centerX, y);
            window.draw(dash);
        }
    }
}

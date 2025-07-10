#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include "menu.hpp"
#include "pong.hpp"
#include "gamestate.hpp"

int main() {
        // --- 1. Récupération de la résolution de l'écran ---
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    unsigned int screenWidth = desktop.width;
    unsigned int screenHeight = desktop.height;

    // --- 2. Création de la fenêtre sans bord, plein écran ---
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Plein écran",
                            sf::Style::None);
    window.setPosition(sf::Vector2i(0, 0));
    window.setFramerateLimit(60);  // Pour éviter de faire tourner à 1000 FPS

    // --- 3. Chargement de la police ---
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur : impossible de charger la police arial.ttf\n";
        return -1;
    }

    // --- 4. États du jeu ---
    GameState state = GameState::Menu;
    Menu menu(font, window.getSize().x);
    Pong pong(font, window.getSize());

    // Boucle principale
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Fermeture
            if (event.type == sf::Event::Closed)
                window.close();

            // Click sur le menu
            if (state == GameState::Menu && event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                menu.handleClick(mousePos, state);

                // Lancement du jeu → reset
                if (state == GameState::Playing)
                    pong.reset(window.getSize());
            }

            // Échap pendant le jeu → retour au menu
            if (state == GameState::Playing &&
                event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape) {
                state = GameState::Menu;
            }
        }

        // Retour au menu si un joueur gagne
        if (state == GameState::Playing && pong.joueurAGagne()) {
            state = GameState::Menu;
            pong.reset(window.getSize());
        }

        // Si le joueur a cliqué sur "Quitter"
        if (state == GameState::Exit)
            window.close();

        // Rendu
        window.clear(sf::Color::Black);

        if (state == GameState::Menu) {
            menu.draw(window);
        } else if (state == GameState::Playing) {
            pong.update(window);
            pong.draw(window);
        }

        window.display();
    }

    return 0;
}

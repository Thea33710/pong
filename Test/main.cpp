#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include "menu.hpp"
#include "pong.hpp"
#include "gamestate.hpp"
#include "gamesettings.hpp"
#include "options.hpp"

int main() {
        // --- 1. Récupération de la résolution de l'écran ---
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    unsigned int screenWidth = desktop.width;
    unsigned int screenHeight = desktop.height;

    // --- 2. Création de la fenêtre sans bord, plein écran ---
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Plein écran", sf::Style::None);
    window.setPosition(sf::Vector2i(0, 0));
    window.setFramerateLimit(60);  // Pour éviter de faire tourner à 1000 FPS

    // --- 3. Chargement de la police ---
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur : impossible de charger la police arial.ttf\n";
        return -1;
    }

    // Initialisation des états et paramètres
    GameState state = GameState::Menu;
    GameSettings settings;  // Structure des paramètres du jeu
    Menu menu(font, screenWidth, screenHeight);
    Pong pong(font, window.getSize());
    OptionsMenu options(font, window.getSize(), settings);

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
            menu.handleClick(event, mousePos, state);

            if (state == GameState::Playing)
            pong.reset(window.getSize());
        }

             // Click dans les options
            if (state == GameState::Options && event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                options.handleClick(event, mousePos);

                if (options.wantsToReturn()) {
                    state = GameState::Menu;
                }
            }

            // Gestion échap
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) 
            {
                if (state == GameState::Playing)
                    state = GameState::Menu;
                else if (state == GameState::Options)
                    state = GameState::Menu; // ← Retour au menu depuis options
                else if (state == GameState::Menu)
                    state = GameState::Exit;
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
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            menu.update(mousePos);  // ← Ajout important
            menu.draw(window);
        } else if (state == GameState::Playing) 
        {
            pong.update(window);
            pong.draw(window);
        }

        window.display();
    }

    return 0;
}

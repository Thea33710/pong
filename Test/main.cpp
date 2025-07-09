#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include "menu.hpp"
#include "pong.hpp"

int main() {
    // --- 1. Récupération de la zone visible de l'écran (hors barre des tâches) ---
    RECT workArea;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);
    int targetWidth = workArea.right - workArea.left;
    int targetHeight = workArea.bottom - workArea.top;

    // --- 2. Calcul de la taille client pour que la FENÊTRE ENTIÈRE tienne dans la zone ---
    DWORD style = WS_OVERLAPPEDWINDOW;
    DWORD exStyle = WS_EX_APPWINDOW;

    RECT windowRect = { 0, 0, targetWidth, targetHeight };
    AdjustWindowRectEx(&windowRect, style, FALSE, exStyle);

    int fullWidth = windowRect.right - windowRect.left;
    int fullHeight = windowRect.bottom - windowRect.top;

    int clientWidth = targetWidth - (fullWidth - targetWidth);
    int clientHeight = targetHeight - (fullHeight - targetHeight);

    // --- 3. Création de la fenêtre SFML ---
    sf::RenderWindow window(sf::VideoMode(clientWidth, clientHeight), "Pong", sf::Style::Default);
    window.setFramerateLimit(60);
    window.setPosition(sf::Vector2i(workArea.left, workArea.top));

    // --- 4. Chargement de la police ---
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur : impossible de charger la police arial.ttf\n";
        return -1;
    }

    // --- 5. États du jeu ---
    GameState state = GameState::Menu;
    Menu menu(font, window.getSize().x);
    Pong pong(font, window.getSize());

    // --- 6. Boucle principale ---
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Fermer la fenêtre
            if (event.type == sf::Event::Closed)
                window.close();

            // Clic sur le menu
            if (state == GameState::Menu && event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                menu.handleClick(mousePos, state);
                if (state == GameState::Playing)
                    pong.reset(window.getSize());
            }

            // Touche Échap pendant le jeu → retour au menu
            if (state == GameState::Playing &&
                event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape) {
                state = GameState::Menu;
            }
        }

        // Si le joueur a cliqué sur "Quitter"
        if (state == GameState::Exit)
            window.close();

        // Affichage
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

#pragma once
#include <SFML/Window.hpp>
#include <map>

struct GameSettings {
    // Résolution et affichage
    bool fullscreen = true;
    sf::Vector2u resolution = {1280, 720};

    // Contrôles
    std::map<std::string, sf::Keyboard::Key> controls = {
        {"left_up", sf::Keyboard::Z},
        {"left_down", sf::Keyboard::S},
        {"right_up", sf::Keyboard::Up},
        {"right_down", sf::Keyboard::Down}
    };

    // Vitesse
    float paddleSpeed = 5.f;
    float ballSpeed = 5.f;

    // Son
    float volume = 100.f; // de 0 à 100

    // Victoire
    int scoreToWin = 5;
};

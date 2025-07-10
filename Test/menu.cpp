#include "menu.hpp"

Menu::Menu(sf::Font& font, float screenWidth, float screenHeight) {
    // Titre
    titre.setFont(font);
    titre.setString("MENU PRINCIPAL");
    titre.setCharacterSize(60);
    titre.setFillColor(sf::Color::White);

    // Boutons
    std::vector<std::string> noms = { "Jouer", "Options", "Quitter" };

    for (const std::string& nom : noms) {
        sf::Text bouton;
        bouton.setFont(font);
        bouton.setString(nom);
        bouton.setCharacterSize(40);
        bouton.setFillColor(sf::Color::White);
        boutons.push_back(bouton);
    }

    // Centrage
    centerMenu(screenWidth, screenHeight);
}

void Menu::centerMenu(float screenWidth, float screenHeight) {
    float spacing = 40.f;  // Espace entre les éléments
    float totalHeight = titre.getLocalBounds().height + spacing;

    for (const auto& b : boutons)
        totalHeight += b.getLocalBounds().height + spacing;

    float startY = (screenHeight - totalHeight) / 2.f;

    // Centrage du titre
    sf::FloatRect titleBounds = titre.getLocalBounds();
    titre.setOrigin(titleBounds.width / 2.f, titleBounds.height / 2.f);
    titre.setPosition(screenWidth / 2.f, startY);
    startY += titleBounds.height + spacing;

    // Centrage des boutons
    for (auto& b : boutons) {
        sf::FloatRect bounds = b.getLocalBounds();
        b.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
        b.setPosition(screenWidth / 2.f, startY);
        startY += bounds.height + spacing;
    }
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(titre);
    for (const auto& bouton : boutons)
        window.draw(bouton);
}

void Menu::handleClick(const sf::Vector2f& mousePos, GameState& state) {
    for (const auto& bouton : boutons) {
        if (bouton.getGlobalBounds().contains(mousePos)) {
            std::string text = bouton.getString();

            if (text == "Jouer") state = GameState::Playing;
            else if (text == "Quitter") state = GameState::Exit;
            // "Options" est ignoré ici
        }
    }
}

#include "menu.hpp"

Menu::Menu(const sf::Font& font, float screenWidth, float screenHeight) {
    titre.setFont(font);
    titre.setString("MENU PRINCIPAL");
    titre.setCharacterSize(60);
    titre.setFillColor(sf::Color::White);

    std::vector<std::string> noms = { "Jouer", "Options", "Quitter" };

    for (const auto& nom : noms) {
        Button bouton(nom, font, 30, sf::Vector2f(300, 60));
        boutons.push_back(bouton);
    }

    centerMenu(screenWidth, screenHeight);
}

void Menu::centerMenu(float screenWidth, float screenHeight) {
    float spacing = 30.f;
    float totalHeight = titre.getLocalBounds().height + spacing + boutons.size() * (60 + spacing);
    float startY = (screenHeight - totalHeight) / 2.f;

    sf::FloatRect titleBounds = titre.getLocalBounds();
    titre.setOrigin(titleBounds.width / 2.f, titleBounds.height / 2.f);
    titre.setPosition(screenWidth / 2.f, startY);
    startY += titleBounds.height + spacing;

    for (auto& b : boutons) {
        b.setPosition(screenWidth / 2.f - 150.f, startY); // 300px de large
        startY += 60 + spacing;
    }
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(titre);
    for (auto& bouton : boutons)
        bouton.draw(window);
}

void Menu::update(const sf::Vector2f& mousePos) {
    for (auto& bouton : boutons)
        bouton.update(mousePos);
}

void Menu::handleClick(const sf::Event& event, const sf::Vector2f& mousePos, GameState& state) {
    for (auto& bouton : boutons) {
        if (bouton.handleClickEvent(event, mousePos)) {
            std::string text = bouton.getText();

            if (text == "Jouer") state = GameState::Playing;
            else if (text == "Options") state = GameState::Options;
            else if (text == "Quitter") state = GameState::Exit;
        }
    }
}


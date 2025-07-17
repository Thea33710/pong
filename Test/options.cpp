#include "options.hpp"

OptionsMenu::OptionsMenu(const sf::Font& font, sf::Vector2u windowSize, GameSettings& settingsRef)
    : settings(settingsRef)
{
    setupMenu(windowSize, font);
}

void OptionsMenu::setupMenu(sf::Vector2u windowSize, const sf::Font& font) {
    titre.setFont(font);
    titre.setString("OPTIONS");
    titre.setCharacterSize(50);
    titre.setFillColor(sf::Color::White);
    sf::FloatRect tb = titre.getLocalBounds();
    titre.setOrigin(tb.width / 2.f, tb.height / 2.f);
    titre.setPosition(windowSize.x / 2.f, 80.f);

    std::vector<std::string> labels = {
        "Resolution", 
        "Plein ecran", 
        "Touches", 
        "Vitesse", 
        "Volume", 
        "Score Max", 
        "Retour"
    };

    float startY = 180.f;
    float spacing = 20.f;

    for (const auto& label : labels) {
        Button b(label, font, 24, sf::Vector2f(300.f, 50.f));
        b.setPosition(windowSize.x / 2.f - 150.f, startY);
        boutons.push_back(b);
        startY += 50.f + spacing;
    }
}

void OptionsMenu::update(const sf::Vector2f& mousePos) {
    for (auto& b : boutons)
        b.update(mousePos);
}

void OptionsMenu::draw(sf::RenderWindow& window) {
    window.draw(titre);
    for (auto& b : boutons)
        b.draw(window);
}

void OptionsMenu::handleClick(const sf::Event& event, const sf::Vector2f& mousePos) {
    for (auto& b : boutons) {
        if (b.handleClickEvent(event, mousePos)) {
            std::string label = b.getText();
            if (label == "Retour") {
                retourVersMenu = true;
            }
            // Tu peux ajouter d'autres conditions ici pour ouvrir des sous-menus
        }
    }
}

bool OptionsMenu::wantsToReturn() const {
    return retourVersMenu;
}

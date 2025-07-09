#include "menu.hpp"

void centerText(sf::Text& text, float y, unsigned int windowWidth) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.width / 2, bounds.height / 2);
    text.setPosition(windowWidth / 2.f, y);
}

Menu::Menu(sf::Font& font, unsigned int windowWidth) {
    title.setFont(font);
    title.setString("MENU PRINCIPAL");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    centerText(title, 100.f, windowWidth);

    playButton.setFont(font);
    playButton.setString("Jouer");
    playButton.setCharacterSize(40);
    playButton.setFillColor(sf::Color::White);
    centerText(playButton, 200.f, windowWidth);

    optionsButton.setFont(font);
    optionsButton.setString("Options");
    optionsButton.setCharacterSize(40);
    optionsButton.setFillColor(sf::Color::White);
    centerText(optionsButton, 280.f, windowWidth);

    quitButton.setFont(font);
    quitButton.setString("Quitter");
    quitButton.setCharacterSize(40);
    quitButton.setFillColor(sf::Color::White);
    centerText(quitButton, 360.f, windowWidth);
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(title);
    window.draw(playButton);
    window.draw(optionsButton);
    window.draw(quitButton);
}

void Menu::handleClick(const sf::Vector2f& mousePos, GameState& state) {
    if (playButton.getGlobalBounds().contains(mousePos)) {
        state = GameState::Playing;
    } else if (optionsButton.getGlobalBounds().contains(mousePos)) {
        state = GameState::Options;
    } else if (quitButton.getGlobalBounds().contains(mousePos)) {
        state = GameState::Exit;
    }
}

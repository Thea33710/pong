#include "button.hpp"
#include <iostream>

Button::Button(const std::string& str, const sf::Font& font, unsigned int charSize, sf::Vector2f size)
    : idleColor(sf::Color::White), hoverColor(sf::Color::Cyan)
{
    shape.setSize(size);
    shape.setFillColor(idleColor);

    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(charSize);
    text.setFillColor(sf::Color::Black);

    // Chargement du son
    if (!clickBuffer.loadFromFile("click.wav")) {
        std::cerr << "Erreur : impossible de charger click.wav\n";
    } else {
        clickSound.setBuffer(clickBuffer);
    }
}

void Button::setPosition(float x, float y) {
    shape.setPosition(x, y);
    sf::FloatRect bounds = text.getLocalBounds();
    text.setPosition(
        x + (shape.getSize().x - bounds.width) / 2.f - bounds.left,
        y + (shape.getSize().y - bounds.height) / 2.f - bounds.top
    );
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}

bool Button::isHovered(const sf::Vector2f& mousePos) const {
    bool inside = shape.getGlobalBounds().contains(mousePos);
    return inside;
}

bool Button::isClicked(const sf::Vector2f& mousePos) const {
    return isHovered(mousePos);
}

void Button::setIdleColor(const sf::Color& color) {
    idleColor = color;
    shape.setFillColor(color);
}

void Button::setHoverColor(const sf::Color& color) {
    hoverColor = color;
}

void Button::update(const sf::Vector2f& mousePos) {
    if (isHovered(mousePos))
        shape.setFillColor(hoverColor);
    else
        shape.setFillColor(idleColor);
}

std::string Button::getText() const {
    return text.getString();
}

void Button::playClickSound() {
     std::cout << "click!" << std::endl;
    clickSound.setVolume(100.f); 
    clickSound.play();
}

bool Button::handleClickEvent(const sf::Event& event, const sf::Vector2f& mousePos) {
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left &&
        isHovered(mousePos)) {
        playClickSound();
        return true;
    }
    return false;
}

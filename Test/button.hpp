#pragma once
#include <SFML/Graphics.hpp>

class Button {
public:
    Button(const std::string& text, const sf::Font& font, unsigned int charSize, sf::Vector2f size);

    void setPosition(float x, float y);
    void draw(sf::RenderWindow& window);
    bool isHovered(const sf::Vector2f& mousePos) const;
    bool isClicked(const sf::Vector2f& mousePos) const;

    void setIdleColor(const sf::Color& color);
    void setHoverColor(const sf::Color& color);
    void update(const sf::Vector2f& mousePos);

    std::string getText() const;

private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Color idleColor;
    sf::Color hoverColor;
};

#include "pong.hpp"
#include <string>

Pong::Pong(sf::Font& font, sf::Vector2u size) {
    leftPaddle.setSize(sf::Vector2f(10.f, 100.f));
    rightPaddle.setSize(sf::Vector2f(10.f, 100.f));
    leftPaddle.setFillColor(sf::Color::White);
    rightPaddle.setFillColor(sf::Color::White);

    ball.setRadius(10.f);
    ball.setFillColor(sf::Color::White);

    scoreText.setFont(font);
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(sf::Color::White);

    reset(size);
}

void Pong::reset(sf::Vector2u size) {
    leftPaddle.setPosition(50.f, size.y / 2.f - leftPaddle.getSize().y / 2.f);
    rightPaddle.setPosition(size.x - 60.f, size.y / 2.f - rightPaddle.getSize().y / 2.f);
    ball.setPosition(size.x / 2.f - ball.getRadius(), size.y / 2.f - ball.getRadius());
    ballVelocity = sf::Vector2f(-4.f, -4.f);
    scoreLeft = 0;
    scoreRight = 0;
    scoreText.setString("0   |   0");
}

void Pong::handleControls(sf::Vector2u size) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && leftPaddle.getPosition().y > 0)
        leftPaddle.move(0.f, -5.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
        leftPaddle.getPosition().y + leftPaddle.getSize().y < size.y)
        leftPaddle.move(0.f, 5.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rightPaddle.getPosition().y > 0)
        rightPaddle.move(0.f, -5.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
        rightPaddle.getPosition().y + rightPaddle.getSize().y < size.y)
        rightPaddle.move(0.f, 5.f);
}

void Pong::handleCollisions(sf::RenderWindow& window) {
    sf::Vector2u size = window.getSize();
    float ballTop = ball.getPosition().y;
    float ballBottom = ball.getPosition().y + ball.getRadius() * 2.f;

    // Rebond haut et bas : exactement dans la zone visible SFML
    if (ballTop <= 0 || ballBottom >= size.y)
        ballVelocity.y = -ballVelocity.y;

    if (ball.getGlobalBounds().intersects(leftPaddle.getGlobalBounds()) ||
        ball.getGlobalBounds().intersects(rightPaddle.getGlobalBounds())) {
        ballVelocity.x = -ballVelocity.x;
    }

    if (ball.getPosition().x < 0) {
        scoreRight++;
        ball.setPosition(size.x / 2.f - ball.getRadius(), size.y / 2.f - ball.getRadius());
        ballVelocity.x = 4.f;
    }

    if (ball.getPosition().x > size.x) {
        scoreLeft++;
        ball.setPosition(size.x / 2.f - ball.getRadius(), size.y / 2.f - ball.getRadius());
        ballVelocity.x = -4.f;
    }

    scoreText.setString(std::to_string(scoreLeft) + "   |   " + std::to_string(scoreRight));
}

void Pong::update(sf::RenderWindow& window) {
    sf::Vector2u size = window.getSize();
    handleControls(size);
    ball.move(ballVelocity);
    handleCollisions(window);

    sf::FloatRect bounds = scoreText.getLocalBounds();
    scoreText.setOrigin(bounds.width / 2, 0);
    scoreText.setPosition(size.x / 2.f, 20.f);
}

void Pong::draw(sf::RenderWindow& window) {
    window.draw(leftPaddle);
    window.draw(rightPaddle);
    window.draw(ball);
    window.draw(scoreText);
}

#include <SFML/Audio.hpp>
#include <iostream>

int main() {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("click.wav")) {
        std::cerr << "Erreur de chargement\n";
        return 1;
    }

    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    std::cout << "Lecture...\n";
    sf::sleep(sf::seconds(2));  // attendre que le son joue
    return 0;
}

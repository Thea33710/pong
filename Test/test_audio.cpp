#include <SFML/Audio.hpp>
#include <iostream>

int main() {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("click.wav")) {
        std::cerr << "Erreur : impossible de charger click.wav\n";
        return 1;
    }

    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    std::cout << "Lecture du son...\n";
    sf::sleep(sf::seconds(2));  // Attente pour que le son joue
    return 0;
}

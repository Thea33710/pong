#include <SFML/Audio.hpp>
#include <iostream>

int main() {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("click.wav")) {
        std::cerr << "Erreur chargement du son\n";
        return 1;
    }

    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    std::cout << "Son joué. Attente...\n";
    sf::sleep(sf::seconds(1)); // Attente pendant que le son joue

    return 0;
}

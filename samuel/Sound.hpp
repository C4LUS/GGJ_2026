#ifndef SOUND_HPP
#define SOUND_HPP

#include <SFML/Audio.hpp>
#include <string>
#include <iostream>

class Sound {
public:
    Sound(std::string path) {
        // 1. Charger le fichier dans le buffer
        if (!buffer.loadFromFile(path)) {
            std::cerr << "Erreur : Impossible de charger le son " << path << std::endl;
        }
        // 2. Lier le buffer au son
        sound.setBuffer(buffer);
    }

    void play() {
        sound.play();
    }

    void stop() {
        sound.stop();
    }

    // Pour régler le volume (0 à 100)
    void setVolume(float volume) {
        sound.setVolume(volume);
    }

    // Pour faire boucler le son (utile pour des bruits d'ambiance)
    void setLoop(bool loop) {
        sound.setLoop(loop);
    }

private:
    sf::SoundBuffer buffer; // Les données audio
    sf::Sound sound;        // Le joueur
};

#endif
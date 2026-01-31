#ifndef ASSETS_HPP
#define ASSETS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <iostream>
#include "GameId.hpp" // Ton fichier d'enum

class Assets {
public:
    // Le constructeur va tout charger tout seul
    Assets(); 
    
    // --- ACCÈS ---
    // C'est tout ce que le public a le droit de demander
    sf::Texture& get(GameID::Texture id);
    sf::Font& get(GameID::Font id);
    sf::SoundBuffer& get(GameID::Sound id);

private:
    // Ces fonctions sont maintenant privées (helpers internes)
    void loadTexture(GameID::Texture id, const std::string& filename);
    void loadFont(GameID::Font id, const std::string& filename);
    void loadSound(GameID::Sound id, const std::string& filename);

    // Stockage
    std::map<GameID::Texture, sf::Texture>   _textures;
    std::map<GameID::Font, sf::Font>         _fonts;
    std::map<GameID::Sound, sf::SoundBuffer> _sounds;
};

#endif
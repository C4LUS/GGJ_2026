#include "../include/Assets.hpp"

// =========================================================
// CONSTRUCTEUR : C'EST ICI QUE TU LISTES TES FICHIERS
// =========================================================
Assets::Assets() {
    std::cout << "[Assets] Chargement des ressources..." << std::endl;

    // --- 1. TEXTURES ---
    // Associe l'Enum (GameId) -> au Fichier sur le disque

    // Game Entity
    loadTexture(GameID::Texture::PlayerCar,      "assets/Homme_pauvre_final.png");
    loadTexture(GameID::Texture::TrafficCivilian,      "assets/taxi.png");
    loadTexture(GameID::Texture::Background,     "assets/Ville.png");
    
    // Mask
    loadTexture(GameID::Texture::Mask_Alcool,      "assets/masque_alcool.png");
    loadTexture(GameID::Texture::Mask_Stinky,      "assets/masque_a_gaz.png");
    loadTexture(GameID::Texture::Mask_Headset,      "assets/casque_antibruit.png");
    //loadTexture(GameID::Texture::Mask_Coke,      "assets/.png");
    loadTexture(GameID::Texture::Mask_Fat,      "assets/Brocoli.png");

    // --- 2. FONTS ---
    loadFont(GameID::Font::Main, "assets/CyberwayRiders-lg97d.ttf");
    loadFont(GameID::Font::Cyber, "assets/CyberwayRiders-lg97d.ttf");

    // --- 3. SONS ---
    //loadSound(GameID::Sound::UI_Click, "assets/tictac.mp3");
    loadSound(GameID::Sound::Minuteur, "assets/tictac.mp3");
    loadSound(GameID::Sound::Test, "assets/ggjtest.wav");
    
    std::cout << "[Assets] Chargement termine !" << std::endl;
}

// =========================================================
// IMPLEMENTATION DES HELPERS (Ne change pas trop ça)
// =========================================================

void Assets::loadTexture(GameID::Texture id, const std::string& filename) {
    sf::Texture tex;
    if (tex.loadFromFile(filename)) {
        // Optionnel : Pixel Art (si tu veux que tout soit pixelisé par défaut)
        // tex.setSmooth(false); 
        _textures[id] = tex;
    } else {
        std::cerr << "[ERREUR] Texture introuvable : " << filename << std::endl;
        // Optionnel : charger une texture de secours pour éviter le crash
    }
}

void Assets::loadFont(GameID::Font id, const std::string& filename) {
    sf::Font font;
    if (font.loadFromFile(filename)) {
        _fonts[id] = font;
    } else {
        std::cerr << "[ERREUR] Font introuvable : " << filename << std::endl;
    }
}

void Assets::loadSound(GameID::Sound id, const std::string& filename) {
    sf::SoundBuffer buffer;
    if (buffer.loadFromFile(filename)) {
        _sounds[id] = buffer;
    } else {
        std::cerr << "[ERREUR] Son introuvable : " << filename << std::endl;
    }
}

// =========================================================
// IMPLEMENTATION DES GETTERS
// =========================================================

sf::Texture& Assets::get(GameID::Texture id) {
    if (_textures.find(id) == _textures.end()) {
        std::cerr << "[CRITIQUE] Tentative d'acces a une Texture non chargee !" << std::endl;
        exit(EXIT_FAILURE); 
    }
    return _textures.at(id);
}

sf::Font& Assets::get(GameID::Font id) {
    if (_fonts.find(id) == _fonts.end()) {
        std::cerr << "[CRITIQUE] Tentative d'acces a une Font non chargee !" << std::endl;
        exit(EXIT_FAILURE); 
    }
    return _fonts.at(id);
}

sf::SoundBuffer& Assets::get(GameID::Sound id) {
    if (_sounds.find(id) == _sounds.end()) {
        std::cerr << "[CRITIQUE] Tentative d'acces a un Son non charge !" << std::endl;
        exit(EXIT_FAILURE); 
    }
    return _sounds.at(id);
}

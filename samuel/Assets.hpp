#ifndef ASSETS_HPP
#define ASSETS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <type_traits>

enum class TexID {
    PetiGuy,
    ProtoPerso,
    Voiture,
    // Ajoute tes noms ici...
};

class Assets {
public:
    // LE CONSTRUCTEUR : Beaucoup plus court !
    Assets(const std::vector<std::string>& texturePaths, 
           const std::vector<std::string>& fontPaths, 
           const std::vector<std::string>& soundPaths) 
    {
        // On appelle notre méthode générique pour chaque catégorie
        loadCategory<sf::Texture>(texturePaths, _textures);
        loadCategory<sf::Font>(fontPaths, _fonts);
        loadCategory<sf::SoundBuffer>(soundPaths, _sounds);
    }

    sf::Texture& getTexture(const std::string& name) { 
        // Petite sécurité que j'ai ajoutée tout à l'heure
        if (_textures.find(name) == _textures.end()) {
            std::cerr << "[ERREUR] Texture introuvable : " << name << std::endl;
            exit(EXIT_FAILURE);
        }
        return _textures.at(name); 
    }

    // --- 2. LA NOUVELLE MÉTHODE AVEC ENUM ---
    // C'est celle-là que tu voulais !
    sf::Texture& get(TexID id) {
        // On traduit l'ID en String, puis on appelle l'autre méthode
        std::string name = enumToString(id);
        return getTexture(name);
    }

    // --- ACCÈS (Ça ne change pas, on garde la sécurité des types) ---
    sf::Font& getFont(const std::string& name)       { return _fonts.at(name); }
    sf::SoundBuffer& getSound(const std::string& name){ return _sounds.at(name); }

private:
    // --- MAPS DE STOCKAGE (On garde les 3 séparées) ---
    std::map<std::string, sf::Texture> _textures;
    std::map<std::string, sf::Font>    _fonts;
    std::map<std::string, sf::SoundBuffer> _sounds;

    std::string enumToString(TexID id) {
        switch (id) {
            case TexID::PetiGuy:    return "peti_guy";    // Doit correspondre à peti_guy.png
            case TexID::ProtoPerso: return "proto_perso"; // Doit correspondre à proto_perso.png
            case TexID::Voiture:    return "voiture";
            default: return "unknown";
        }
    }
    // --- LA MAGIE DES TEMPLATES ---
    // T = Le type de ressource (sf::Texture, sf::Font, etc.)
    template <typename T>
    void loadCategory(const std::vector<std::string>& paths, std::map<std::string, T>& targetMap) {
        for (const auto& path : paths) {
            T resource;
            // Toutes les classes SFML ont cette méthode, donc le template compile !
            if (resource.loadFromFile(path)) {

                // Petit bonus : Si c'est une Texture, on met le Pixel Art
                // "if constexpr" (C++17) permet de faire du code spécifique selon le type
                if constexpr (std::is_same_v<T, sf::Texture>) {
                    resource.setSmooth(false);
                }

                std::string name = extractName(path);
                targetMap[name] = resource;
                std::cout << "[Assets] Charge : " << name << std::endl;
            } else {
                std::cerr << "[Erreur] Fichier introuvable : " << path << std::endl;
            }
        }
    }

    // Utilitaire
    std::string extractName(std::string path) {
        size_t lastSlash = path.find_last_of("/\\");
        size_t lastDot = path.find_last_of(".");
        size_t start = (lastSlash == std::string::npos) ? 0 : lastSlash + 1;
        return path.substr(start, lastDot - start);
    }
};

#endif
#include "Assets.hpp"
#include "Character.hpp"
// #include "Word.hpp" // Décommente si tu as créé ce fichier
#include <iostream>
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "RaMasqueMoi");
    window.setFramerateLimit(60); // IMPORTANT : Limite les FPS pour ne pas surchauffer le CPU
    sf::Clock clock;

    // --- 1. PRÉPARATION ---
    std::vector<std::string> textures = {
        "assets/proto_perso.png",
        "assets/peti_guy.png"
    };

    std::vector<std::string> fonts = {
        "assets/CyberwayRiders-lg97d.ttf"
    };

    std::vector<std::string> sounds = {
        "assets/tictac.mp3"
    };

    // --- 2. CHARGEMENT ---
    Assets assets(textures, fonts, sounds);

    // --- 3. CRÉATION DES OBJETS ---
    // Vérifie bien que "assets/peti_guy.png" existe et que c'est une SpriteSheet
    // Ici : Frame de 32x32 pixels, commence à (0,0), et contient 3 images d'animation.
    Character hero(assets, "peti_guy", 16, 16, 2, 2, 3);

    // Ajout d'une animation "run" (exemple)
    hero.addAnimation("run", 2+ (3 * 16), 2, 16, 16, 3, 0.2f);

    // Positionnement initial
    hero.setPosition(400, 300);
    hero.setScale(4.0f, 4.0f);

    // --- 4. BOUCLE DE JEU ---
    while (window.isOpen()) {
        

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Gestion des touches "Appuyées une seule fois"
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            hero.setAnimation("run");
        } else {
            hero.setAnimation("default");
        }

        sf::Time dt = clock.restart();

        // Update
        hero.updateAnimation(dt.asSeconds());

        // Draw
        window.clear(sf::Color(50, 50, 50)); // Gris foncé pour mieux voir
        window.draw(hero);
        window.display();
    }

    return EXIT_SUCCESS;
}
#include <SFML/Graphics.hpp>
#include "../include/Assets.hpp"
#include "../include/Character.hpp"
#include "../include/GameId.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "RaMasqueMoi");
    window.setFramerateLimit(60);

    // 1. Juste une ligne ! 
    // Le constructeur d'Assets va lire sa liste interne et tout charger.
    Assets assets; 

    // 2. On utilise l'Enum pour créer le perso
    Character hero(assets, GameID::Texture::PlayerCar, 32, 32, 0, 0, 3);
    
    // ... reste du code ...
    hero.setPosition(200, 200);
    hero.setScale(4, 4);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear();
        window.draw(hero);
        window.display();
    }

    return 0;
}
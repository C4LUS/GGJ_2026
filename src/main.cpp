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

    sf::Sprite background;
    background.setTexture(assets.get(GameID::Texture::Background));
    // Optionnel : Forcer le fond à faire la taille de la fenêtre
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = background.getTexture()->getSize();
    background.setScale(
        (float)windowSize.x / textureSize.x,
        (float)windowSize.y / textureSize.y
    );
    // 2. On utilise l'Enum pour créer le perso
    Character hero(assets, GameID::Texture::PlayerCar, 90, 200, 0, 0, 4);

    // ... reste du code ...
    hero.setPosition(200, 500);
    hero.setScale(0.5, 0.5);

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        float deltaTimeSeconds = dt.asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    //
                }
            }
        }
        hero.move(40 * deltaTimeSeconds, 0.f);
        hero.update(deltaTimeSeconds);
        window.clear();
        window.draw(background);
        window.draw(hero);
        window.display();
    }

    return 0;
}
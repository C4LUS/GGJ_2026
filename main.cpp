#include <SFML/Graphics.hpp>
#include "include/InsideCar.hpp"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "PhoneSystem Test");
    window.setFramerateLimit(60);

    TextureHolder textures;
    Context context;
    context.window = &window;
    context.textures = &textures;

    PhoneSystem phone(textures);
    MaskSelector maskSelector(context);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            phone.handleEvent(event, window);

            // ⬇️ on ne passe les events au MaskSelector
            // QUE quand le phone attend un choix
            if (phone.isWaitingForMask()) {
                maskSelector.handleEvent(event);
            }
        }

        sf::Time dt = clock.restart();
        phone.update(dt);

        // ---------- LOGIQUE DE JEU ----------
        if (phone.isWaitingForMask()) {
            GameID::Malus selected = maskSelector.getSelectedMask();
            if (selected != GameID::Malus::None) {
                if (selected == phone.getRequiredMask())
                    std::cout << "Correct malus!" << std::endl;
                else
                    std::cout << "Wrong malus!" << std::endl;

                // reset propre
                maskSelector = MaskSelector(context);
                phone.reset();
            }
        }

        // ---------- RENDER ----------
        window.clear(sf::Color::Black);
        window.draw(phone);

        if (phone.isWaitingForMask()) {
            window.draw(maskSelector);
        }

        window.display();
    }

    return 0;
}


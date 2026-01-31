#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Car.hpp"
#include "Road.hpp"
#include "ObstacleWood.hpp"

#define ROAD_POS sf::Vector2f(960.0f, 540.0f)
#define ROAD_SIZE sf::Vector2f(1000.0f, 1080.0f)
#define WOOD_POS sf::Vector2f(1000.0f, 0.0f)
#define WOOD_SIZE sf::Vector2f(100.0f, 20.0f)

int main()
{
    sf::RectangleShape mid;
    Road road = Road(ROAD_SIZE, ROAD_POS);
    Car car = Car();
    ObstacleWood wood = ObstacleWood(WOOD_POS, WOOD_SIZE);
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "");
    window.setFramerateLimit(60);


    mid.setOrigin(sf::Vector2f(2.5f, 2.5f));
    mid.setSize(sf::Vector2f(5.0f, 5.0f));
    mid.setFillColor(sf::Color::Red);
    mid.setPosition(sf::Vector2f(960.0f, 540.0f));

    wood.setDisplay(true);
    std::cout << "display: " << wood.getDisplay() << ", pos: " << wood.getPos().x << wood.getPos().y << std::endl;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) {
            car.goLeft(road);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) {
            car.goRight(road);
        }
        window.clear(sf::Color::Green);
        road.display(window);
        wood.Display(window);
        car.display(window);
        window.draw(mid);
        window.display();
    }
    return 0;
}

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Car.hpp"
#include "Road.hpp"
#include "ObstacleWood.hpp"
#include "ObstacleGoat.hpp"
#include "ObstacleGuy.hpp"
#include "ObstacleFactory.hpp"
#include "ObstacleSpwaner.hpp"

int main()
{
    sf::RectangleShape mid;
    Road road = Road(ROAD_SIZE, ROAD_POS);
    Car car = Car(CAR_POS, CAR_SIZE);

    
    ObstacleFactory obstaclefactory = ObstacleFactory();
    ObstacleSpawner obstaclespawner = ObstacleSpawner(obstaclefactory);


    sf::RenderWindow window(sf::VideoMode(1920, 1080), "");
    window.setFramerateLimit(60);
    
    
    mid.setOrigin(sf::Vector2f(2.5f, 2.5f));
    mid.setSize(sf::Vector2f(5.0f, 5.0f));
    mid.setFillColor(sf::Color::Red);
    mid.setPosition(sf::Vector2f(960.0f, 540.0f));
    
    srand(time(0));
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
        obstaclespawner.spawnObstacle(window, car);
        car.display(window);

        window.draw(mid);
        window.display();
    }
    return 0;
}

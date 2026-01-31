#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Car.hpp"
#include "Road.hpp"
#include "ObstacleWood.hpp"
#include "ObstacleGoat.hpp"
#include "ObstacleGuy.hpp"

#define ROAD_POS sf::Vector2f(960.0f, 540.0f)
#define ROAD_SIZE sf::Vector2f(1000.0f, 1080.0f)

#define WOOD_POS sf::Vector2f(960.0f, 50.0f)
#define WOOD_SIZE sf::Vector2f(100.0f, 30.0f)

#define GOAT_POS sf::Vector2f(960.0f, 50.0f)
#define GOAT_SIZE sf::Vector2f(50.0f, 25.0f)

#define GUY_POS sf::Vector2f(960.0f, 50.0f)
#define GUY_SIZE sf::Vector2f(30.0f, 30.0f)

#define CAR_POS sf::Vector2f(960.0f, 1000.0f)
#define CAR_SIZE sf::Vector2f(50.0f, 100.0f)

int main()
{
    sf::RectangleShape mid;
    Road road = Road(ROAD_SIZE, ROAD_POS);
    Car car = Car(CAR_POS, CAR_SIZE);

    ObstacleGoat goat = ObstacleGoat(GOAT_POS, GOAT_SIZE);
    ObstacleWood wood = ObstacleWood(WOOD_POS, WOOD_SIZE);
    ObstacleGuy guy = ObstacleGuy(GUY_POS, GUY_SIZE);
    


    sf::RenderWindow window(sf::VideoMode(1920, 1080), "");
    window.setFramerateLimit(60);


    mid.setOrigin(sf::Vector2f(2.5f, 2.5f));
    mid.setSize(sf::Vector2f(5.0f, 5.0f));
    mid.setFillColor(sf::Color::Red);
    mid.setPosition(sf::Vector2f(960.0f, 540.0f));

    guy.setDisplay(true);
    std::cout << "display: " << wood.getDisplay() << ", pos: " << wood.getPos().x << wood.getPos().y << std::endl;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        //wood.is_collide(car);
        //goat.is_collide(car);
        guy.is_collide(car);


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) {
            car.goLeft(road);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) {
            car.goRight(road);
        }
        window.clear(sf::Color::Green);


        road.display(window);
        //wood.Display(window);
        //goat.Display(window);
        guy.Display(window);
        car.display(window);

        window.draw(mid);
        window.display();

        guy.moveObstacle(5);
        //wood.moveObstacle(5);
        //goat.moveObstacle(5);
    }
    return 0;
}

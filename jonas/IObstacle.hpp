
#pragma once

    #include <string>
    #include <iostream>
    #include <SFML/Audio.hpp>
    #include <SFML/Graphics.hpp>

enum ObstacleType {
    WOOD,
    GOAT,
    GUY,
    CAR,
    VAN,
    BUS,
    BIKE,
    CUSTOMIZABLE
};

#define CAR_POS sf::Vector2f(960.0f, 1000.0f)
#define ROAD_POS sf::Vector2f(960.0f, 540.0f)
#define ROAD_SIZE sf::Vector2f(1000.0f, 1080.0f)


#define OBSTACLE_POS sf::Vector2f(960.0f, 50.0f)
#define WOOD_SIZE sf::Vector2f(200.0f, 75.0f)
#define GOAT_SIZE sf::Vector2f(75.0f, 100.0f)
#define GUY_SIZE sf::Vector2f(75.0f, 75.0f)
#define CAR_SIZE sf::Vector2f(100.0f, 150.0f)
#define VAN_SIZE sf::Vector2f(110.0f, 175.0f)
#define BIKE_SIZE sf::Vector2f(40.0f, 60.0f)
#define BUS_SIZE sf::Vector2f(120.0f, 450.0f)
#define CUSTOMIZABLE_SIZE sf::Vector2f(50.0f, 100.0f)

class IObstacle
{
    public:
        virtual ~IObstacle() = default;

        virtual std::tuple<sf::Vector2f, sf::Vector2f> getHitbox() const = 0;
        virtual ObstacleType getType() const = 0;
        virtual sf::Vector2f getPos() const = 0;
        virtual size_t Attack() const = 0;
        virtual bool getDisplay() const = 0;
        virtual void setDisplay(bool displayable) = 0;
        virtual void Display(sf::RenderWindow& window) const = 0;
        virtual void moveObstacle(size_t speed) = 0;
        virtual bool is_collide(Car& car) = 0;
        virtual bool is_alive() const = 0;
        virtual void randomizePosRoad() = 0;
};


#pragma once

    #include <string>
    #include <iostream>

enum ObstacleType {
    WOOD,
    GOAT,
    GUY
};

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
};

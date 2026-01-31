
#pragma once

#include "IObstacle.hpp"

class AObstacle : public IObstacle
{
    public:
        virtual ~AObstacle() = default;

        std::tuple<sf::Vector2f, sf::Vector2f> getHitbox() const override
        {
            return this->_hitbox;
        }

        ObstacleType getType() const override
        {
            return this->_type;
        }

        sf::Vector2f getPos() const override
        {
            return this->_pos;
        }

        size_t Attack() const override
        {
            return this->_attack;
        }

        bool getDisplay() const override
        {
            return this->_displayable;
        }

        void setDisplay(bool displayable) override
        {
            this->_displayable = displayable;
        }

        void Display(sf::RenderWindow& window) const override
        {
            if (this->_displayable == false) {
                std::cout << "nononono" << std::endl;
                return;
            }
            std::cout << "oui" << std::endl;
            window.draw(this->_shape);
        }

    protected:
        bool _displayable;
        size_t _attack;
        std::tuple<sf::Vector2f, sf::Vector2f> _hitbox;
        sf::Vector2f _size;
        sf::Vector2f _pos;
        ObstacleType _type;
        sf::RectangleShape _shape;
};


#pragma once

#include "AObstacle.hpp"

class ObstacleWood : public AObstacle
{
    public:
        ObstacleWood(sf::Vector2f pos, sf::Vector2f size)
        {
            this->_pos = pos - (size / 2.f);
            this->_size = size;
            this->_type = WOOD;
            this->_attack = 10;
            this->_displayable = true;
            this->_hitbox = std::make_tuple(pos - size, pos + size);

            this->_shape.setOrigin(this->_size / 2.f);
            this->_shape.setSize(this->_size);
            this->_shape.setFillColor(sf::Color::Blue);
            this->_shape.setOutlineThickness(2);
            this->_shape.setPosition(this->_pos);
        }
};

#pragma once

#include "AObstacle.hpp"

class ObstacleBike : public AObstacle
{
    public:
        ObstacleBike(sf::Vector2f pos, sf::Vector2f size)
        {
            this->_alive = true;
            this->_pos = pos;
            this->_size = size;
            this->_type = BIKE;
            this->_attack = 10;
            this->_displayable = false;
            this->_hitbox = std::make_tuple(pos - (size / 2.f), pos + (size / 2.f));

            this->_shape.setOrigin(this->_size / 2.f);
            this->_shape.setSize(this->_size);
            this->_shape.setFillColor(sf::Color::Blue);
            this->_shape.setOutlineThickness(2);
            this->_shape.setPosition(this->_pos);

            this->_hitbox_shape.setSize(this->_size);
            this->_hitbox_shape.setFillColor(sf::Color::Transparent);
            this->_hitbox_shape.setOutlineThickness(2);
            this->_hitbox_shape.setOutlineColor(sf::Color::Green);
            this->_hitbox_shape.setPosition(pos - (size / 2.f));
        }
};
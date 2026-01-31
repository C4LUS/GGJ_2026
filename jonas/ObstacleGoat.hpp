
#pragma once

#include "AObstacle.hpp"

class ObstacleGoat : public AObstacle
{
    public:
        ObstacleGoat(sf::Vector2f pos, sf::Vector2f size)
        {
            //sf::Vector2f hitbox_pos1 = sf::Vector2f(pos.x - (size.x / 2.f), pos.y - (size.y / 2.f));
            //sf::Vector2f hitbox_pos2 = sf::Vector2f(pos.x + (size.x / 2.f), pos.y + (size.y / 2.f));

            this->_pos = pos;
            this->_size = size;
            this->_type = WOOD;
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
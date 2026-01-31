
#pragma once

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Road.hpp"

//class Road;
class Car
{
    public:
        Car(sf::Vector2f pos, sf::Vector2f size)
        {
            //this->_speed = 0;
            this->_display = false;

            this->_pos = pos;
            this->_size = size;
            this->_hitbox = std::make_tuple(pos - (size / 2.f), pos + (size / 2.f));

            this->_shape.setOrigin(this->_size / 2.f);
            this->_shape.setSize(this->_size);
            this->_shape.setFillColor(sf::Color::Red);
            this->_shape.setPosition(this->_pos);

            this->_hitbox_shape.setSize(this->_size);
            this->_hitbox_shape.setFillColor(sf::Color::Transparent);
            this->_hitbox_shape.setOutlineThickness(2);
            this->_hitbox_shape.setOutlineColor(sf::Color::Green);
            this->_hitbox_shape.setPosition(pos - (size / 2.f));
        }

        std::tuple<sf::Vector2f, sf::Vector2f> getHitbox() const
        {
            return this->_hitbox;    
        }

        void goLeft(Road& road)
        {
            const std::tuple<sf::Vector2f, sf::Vector2f> area = road.getArea();

            if (this->_pos.x - 5 < std::get<0>(area).x) {
                return;
            }
            this->_pos.x -= 5;
            std::get<0>(this->_hitbox).x -= 5;
            std::get<1>(this->_hitbox).x -= 5;
            this->_shape.setPosition(this->_pos);
            this->_hitbox_shape.setPosition(this->_pos - (this->_size / 2.f));
            std::cout << _pos.x << std::endl;    
        }

        void goRight(Road& road)
        {
            const std::tuple<sf::Vector2f, sf::Vector2f> area = road.getArea();

            if (this->_pos.x + 5 > std::get<1>(area).x) {
                return;
            }
            this->_pos.x += 5;
            std::get<0>(this->_hitbox).x += 5;
            std::get<1>(this->_hitbox).x += 5;
            this->_shape.setPosition(this->_pos);
            this->_hitbox_shape.setPosition(this->_pos - (this->_size / 2.f));
            std::cout << _pos.x << std::endl;
        }

        void display(sf::RenderWindow& window) const
        {
            window.draw(this->_shape);
            window.draw(this->_hitbox_shape);
        }

        sf::RectangleShape getShape() const
        {
            return this->_shape;
        }

        sf::RectangleShape getHitboxShape() const
        {
            return this->_hitbox_shape;
        }

    private:
        int _speed;
        bool _display;

        sf::Vector2f _pos;
        sf::Vector2f _size;
        std::tuple<sf::Vector2f, sf::Vector2f> _hitbox;
        sf::RectangleShape _shape;
        sf::RectangleShape _hitbox_shape;
};


#pragma once

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Road.hpp"

//class Road;
class Car
{
    public:
        Car()
        {
            this->_speed = 0;
            this->_display = false;

            this->_pos = sf::Vector2f(960.0f, 1000.0f);
            this->_size = sf::Vector2f(50.0f, 50.0f);

            this->_shape.setOrigin(this->_size / 2.f);
            this->_shape.setSize(this->_size);
            this->_shape.setFillColor(sf::Color::Red);
            this->_shape.setOutlineThickness(5);
            this->_shape.setPosition(this->_pos);
        }

        void goLeft(Road& road)
        {
            const std::tuple<sf::Vector2f, sf::Vector2f> area = road.getArea();

            if (this->_pos.x - 5 < std::get<0>(area).x) {
                std::cout << _pos.x << std::endl;
                return;
            }
            this->_pos.x -= 5;
            this->_shape.setPosition(this->_pos);
            std::cout << _pos.x << std::endl;    
        }

        void goRight(Road& road)
        {
            const std::tuple<sf::Vector2f, sf::Vector2f> area = road.getArea();

            if (this->_pos.x + 5 > std::get<1>(area).x) {
                std::cout << _pos.x << std::endl;
                return;
            }
            this->_pos.x += 5;
            this->_shape.setPosition(this->_pos);
            std::cout << _pos.x << std::endl;
        }

        void display(sf::RenderWindow& window) const
        {
            window.draw(this->_shape);
        }

        sf::RectangleShape getShape() const
        {
            return this->_shape;
        }

    private:
        int _speed;
        bool _display;

        sf::Vector2f _pos;
        sf::Vector2f _size;
        //std::tuple<sf::Vector2f, sf::Vector2f> _hitbox;
        sf::RectangleShape _shape;
};

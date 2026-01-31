
#pragma once

#include <SFML/Graphics.hpp>

class Road
{
    public:
        Road(sf::Vector2f size, sf::Vector2f pos)
        {
            this->_size = size;
            this->_pos = pos;
            this->_area = std::tuple<sf::Vector2f, sf::Vector2f>{pos - (size / 2.f), pos + (size / 2.f)};

            this->_shape.setOrigin(this->_size / 2.f);
            this->_shape.setSize(this->_size);
            this->_shape.setFillColor(sf::Color::Black);
            this->_shape.setOutlineThickness(2);
            this->_shape.setPosition(this->_pos);
        }

        void display(sf::RenderWindow &window)
        {
            window.draw(this->_shape);
        }

        std::tuple<sf::Vector2f, sf::Vector2f> getArea() const
        {
            return this->_area;
        }

    private:
        std::tuple<sf::Vector2f, sf::Vector2f> _area;
        sf::Vector2f _pos;
        sf::Vector2f _size;
        sf::RectangleShape _shape;
};

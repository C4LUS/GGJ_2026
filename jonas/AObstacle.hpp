
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
                return;
            }
            window.draw(this->_shape);
            window.draw(this->_hitbox_shape);
        }

        void moveObstacle(size_t speed) override
        {
            
            if (this->_displayable == false ) {
                return;
            }
            this->_pos.y += speed;
            std::get<1>(this->_hitbox).y += speed;
            std::get<0>(this->_hitbox).y += speed;
            this->_shape.setPosition(this->_pos);
            this->_hitbox_shape.setPosition(this->_pos - (_size / 2.0f));
        }

        bool is_collide(Car& car)
        {
            std::tuple<sf::Vector2f, sf::Vector2f> object_hitbox = car.getHitbox();

            float ax1 = std::get<0>(this->_hitbox).x;
            float ax2 = std::get<1>(this->_hitbox).x;
            float ay1 = std::get<0>(this->_hitbox).y;
            float ay2 = std::get<1>(this->_hitbox).y;

            float bx1 = std::get<0>(object_hitbox).x;
            float bx2 = std::get<1>(object_hitbox).x;
            float by1 = std::get<0>(object_hitbox).y;
            float by2 = std::get<1>(object_hitbox).y;

            if ((bx1 > ax1 && bx1 < ax2) && (by1 > ay1 && by1 < ay2)) {
                this->_displayable = false;
                return true;
            }
            if ((bx2 > ax1 && bx2 < ax2) && (by2 > ay1 && by2 < ay2)) {
                this->_displayable = false;
                return true;
            }
            std::cout << "car x1: " << bx1 << "car y1: " << by1 << ", car x2: " << bx2 << "car y2: " << by2 << std::endl;
            std::cout << "obj x1: " << ax1 << "obj y1: " << ay1 << ", obj x2: " << ax2 << "obj y2: " << ay2 << std::endl;
            std::cout << "\n";
            return false;
        }

    protected:
        bool _displayable;
        size_t _attack;
        std::tuple<sf::Vector2f, sf::Vector2f> _hitbox;
        sf::RectangleShape _hitbox_shape;
        sf::Vector2f _size;
        sf::Vector2f _pos;
        ObstacleType _type;
        sf::RectangleShape _shape;
};


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
            sf::FloatRect r1 = car.getHitboxShape().getGlobalBounds();
            sf::FloatRect r2 = this->_hitbox_shape.getGlobalBounds();

            if (r1.intersects(r2)) {
                this->_displayable = false;
                return true;
            }
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

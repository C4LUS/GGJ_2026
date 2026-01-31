#pragma once
#include "SharedContext.hpp"
#include <SFML/Graphics.hpp>

class PlayerCar : public sf::Drawable, public sf::Transformable {
public:
  // CHANGED: Removed 'const' to match Assets::get() signature
  PlayerCar(Assets &assets);

  void update(sf::Time dt,
              const std::tuple<sf::Vector2f, sf::Vector2f> &roadBorders);

  // Connects inputs to movement
  void handleRealtimeInput(const InputManager &input);

  // Collision helpers
  sf::FloatRect getGlobalBounds() const;
  void setVelocity(sf::Vector2f velocity);
  void setPosition(sf::Vector2f position);

private:
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;

private:
  sf::Sprite mSprite;
  sf::Vector2f mVelocity;
  float mSpeed;

  // Hitbox visualization (Debug)
  sf::RectangleShape mHitboxShape;
};

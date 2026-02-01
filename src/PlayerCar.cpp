#include "../include/PlayerCar.hpp"
#include <iostream>

// CHANGED: Removed 'const'
PlayerCar::PlayerCar(Assets &assets)
    : mSprite(), mVelocity(0.f, 0.f), mSpeed(300.f) // Pixel per second
{
  // Try to load texture, fallback to color if missing
  try {
    mSprite.setTexture(assets.get(GameID::Texture::PlayerCar));

    // Center origin based on new texture
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    // Optional: Scale it down if the image is huge
    // mSprite.setScale(0.2f, 0.2f);
  } catch (...) {
    std::cout << "[PlayerCar] Texture not found, sprite might be invisible"
              << std::endl;
  }

  // Debug Hitbox
  mHitboxShape.setSize(sf::Vector2f(40.f, 80.f));
  mHitboxShape.setOrigin(20.f, 40.f);
  mHitboxShape.setFillColor(sf::Color::Red);
}

void PlayerCar::handleRealtimeInput(const InputManager &input) {
  mVelocity.x = 0.f;

  // Use the abstraction!
  if (input.isActionActive(GameID::Action::SteerLeft)) {
    mVelocity.x -= mSpeed;
  }
  if (input.isActionActive(GameID::Action::SteerRight)) {
    mVelocity.x += mSpeed;
  }
}

void PlayerCar::update(
    sf::Time dt, const std::tuple<sf::Vector2f, sf::Vector2f> &roadBorders) {
  // 1. Move
  move(mVelocity * dt.asSeconds());

  // 2. Bound Check (Jonas's logic adapted)
  sf::Vector2f pos = getPosition();
  float halfWidth = 20.f; // Approximate half width of car

  float leftLimit = std::get<0>(roadBorders).x + halfWidth;
  float rightLimit = std::get<1>(roadBorders).x - halfWidth;

  // Clamp Position
  if (pos.x < leftLimit)
    pos.x = leftLimit;
  if (pos.x > rightLimit)
    pos.x = rightLimit;

  setPosition(pos);

  // Sync debug shape
  mHitboxShape.setPosition(pos);
}

void PlayerCar::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  states.transform *= getTransform();
  // Only draw the Red Box if we don't trust the texture yet
  // target.draw(mHitboxShape, states);
  target.draw(mSprite, states);
}

void PlayerCar::setPosition(sf::Vector2f position) {
  sf::Transformable::setPosition(position);
}

sf::FloatRect PlayerCar::getGlobalBounds() const {
  return getTransform().transformRect(mSprite.getGlobalBounds());
}

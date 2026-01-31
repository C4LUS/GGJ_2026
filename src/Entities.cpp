#include "../include/Entities.hpp"
#include <algorithm>
#include <exception>

SceneNode::SceneNode() : mChildren(), mParent(nullptr) {}

void SceneNode::attachChild(Ptr child) {
  child->mParent = this;
  mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode &node) {
  auto found = std::find_if(mChildren.begin(), mChildren.end(),
                            [&node](const Ptr &p) { return p.get() == &node; });
  if (found == mChildren.end()) {
    return Ptr();
  }

  Ptr result = std::move(*found);
  result->mParent = nullptr;
  mChildren.erase(found);
  return result;
}

void SceneNode::update(sf::Time dt) {
  updateCurrent(dt);
  for (const auto &child : mChildren) {
    child->update(dt);
  }
}

sf::Transform SceneNode::getWorldTransform() const {
  sf::Transform transform = sf::Transform::Identity;
  for (const SceneNode *node = this; node != nullptr; node = node->mParent) {
    transform = node->getTransform() * transform;
  }
  return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const {
  return getWorldTransform() * sf::Vector2f();
}

void SceneNode::updateCurrent(sf::Time) {}

void SceneNode::drawCurrent(sf::RenderTarget &, sf::RenderStates) const {}

void SceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  states.transform *= getTransform();
  drawCurrent(target, states);
  for (const auto &child : mChildren) {
    target.draw(*child, states);
  }
}

Entity::Entity() : mVelocity(0.f, 0.f) {}

void Entity::setVelocity(sf::Vector2f velocity) { mVelocity = velocity; }

void Entity::accelerate(sf::Vector2f velocity) { mVelocity += velocity; }

sf::Vector2f Entity::getVelocity() const { return mVelocity; }

void Entity::updateCurrent(sf::Time dt) {
  move(mVelocity * dt.asSeconds());
}

PlayerCar::PlayerCar(const TextureHolder &textures)
    : mSprite(std::nullopt), mFallbackShape({48.f, 80.f}), mSpeed(240.f) {
  mFallbackShape.setFillColor(sf::Color(40, 200, 120));
  mFallbackShape.setOrigin({mFallbackShape.getSize().x / 2.f,
                            mFallbackShape.getSize().y / 2.f});
  try {
    mSprite.emplace(textures.get(GameID::Texture::PlayerCar));
    const sf::FloatRect bounds = mSprite->getLocalBounds();
    mSprite->setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
  } catch (const std::exception &) {
    // Texture not loaded yet; keep empty sprite for now.
  }
}

void PlayerCar::handleRealtimeInput(GameID::Action action) {
  switch (action) {
  case GameID::Action::SteerLeft:
    mVelocity.x = -mSpeed;
    break;
  case GameID::Action::SteerRight:
    mVelocity.x = mSpeed;
    break;
  case GameID::Action::Accelerate:
    mVelocity.y = -mSpeed;
    break;
  case GameID::Action::Brake:
    mVelocity.y = mSpeed;
    break;
  default:
    break;
  }
}

void PlayerCar::updateCurrent(sf::Time dt) {
  Entity::updateCurrent(dt);
  mVelocity = sf::Vector2f();
}

void PlayerCar::drawCurrent(sf::RenderTarget &target,
                            sf::RenderStates states) const {
  if (mSprite.has_value()) {
    target.draw(*mSprite, states);
  } else {
    target.draw(mFallbackShape, states);
  }
}

TrafficCar::TrafficCar(sf::Vector2f size, sf::Color color)
    : mShape(size) {
  mShape.setFillColor(color);
  mShape.setOrigin({size.x / 2.f, size.y / 2.f});
}

sf::Vector2f TrafficCar::getSize() const { return mShape.getSize(); }

void TrafficCar::drawCurrent(sf::RenderTarget &target,
                             sf::RenderStates states) const {
  target.draw(mShape, states);
}

#pragma once
#include "GameId.hpp"
#include "SharedContext.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <optional>
#include <vector>

// Base drawable object generic
class SceneNode : public sf::Transformable, public sf::Drawable {
public:
  typedef std::unique_ptr<SceneNode> Ptr;

  SceneNode();
  virtual ~SceneNode() = default;
  SceneNode(const SceneNode &) = delete;
  SceneNode &operator=(const SceneNode &) = delete;
  SceneNode(SceneNode &&) = delete;
  SceneNode &operator=(SceneNode &&) = delete;

  // allow multiple object to connect and disconnect
  void attachChild(Ptr child);
  Ptr detachChild(const SceneNode &node);

  void update(sf::Time dt);
  sf::Vector2f getWorldPosition() const;
  sf::Transform getWorldTransform() const;

protected:
  virtual void updateCurrent(sf::Time dt);
  virtual void drawCurrent(sf::RenderTarget &target,
                           sf::RenderStates states) const;

private:
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;

  std::vector<Ptr> mChildren;
  SceneNode *mParent;
};

// Moving entities
class Entity : public SceneNode {
public:
  Entity();
  void setVelocity(sf::Vector2f velocity);
  void accelerate(sf::Vector2f velocity);
  sf::Vector2f getVelocity() const;

protected:
  virtual void updateCurrent(sf::Time dt) override;
  sf::Vector2f mVelocity;
};

// player
class PlayerCar : public Entity {
public:
  PlayerCar(const TextureHolder &textures);

  // inputs already altered by maluses manager
  void handleRealtimeInput(GameID::Action action);

  virtual void updateCurrent(sf::Time dt) override;
  virtual void drawCurrent(sf::RenderTarget &target,
                           sf::RenderStates states) const override;

private:
  std::optional<sf::Sprite> mSprite;
  sf::RectangleShape mFallbackShape;
  float mSpeed;
};

// traffic / obstacles
class TrafficCar : public Entity {
public:
  TrafficCar(sf::Vector2f size, sf::Color color);
  sf::Vector2f getSize() const;

  virtual void drawCurrent(sf::RenderTarget &target,
                           sf::RenderStates states) const override;

private:
  sf::RectangleShape mShape;
};

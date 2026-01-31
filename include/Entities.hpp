#pragma once
#include "SharedContext.hpp"
#include <SFML/Graphics.hpp>

// Base drawable object generic
class SceneNode : public sf::Transformable,
                  public sf::Drawable,
                  private sf::NonCopyable {
public:
  typedef std::unique_ptr<SceneNode> Ptr;

  // allow multiple object to connect and disconnect
  void attachChild(Ptr child);
  Ptr detachChild(const SceneNode &node);

  void update(sf::Time dt);
  sf::Vector2f getWorldPosition() const;

private:
  virtual void updateCurrent(sf::Time dt);
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;

  std::vector<Ptr> mChildren;
  SceneNode *mParent;
};

// Moving entities
class Entity : public SceneNode {
public:
  void setVelocity(sf::Vector2f velocity);
  void accelerate(sf::Vector2f velocity);
  sf::Vector2f getVelocity() const;

protected:
  sf::Vector2f mVelocity;
};

// player
class PlayerCar : public Entity {
public:
  PlayerCar(const TextureHolder &textures);

  // inputs already altered by maluses manager
  void handleRealtimeInput(GameID::Action action);

  virtual void updateCurrent(sf::Time dt) override;

private:
  sf::Sprite mSprite;
  float mSpeed;
};

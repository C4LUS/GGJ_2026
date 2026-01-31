#pragma once
#include "Entities.hpp"
#include "MalusSystem.hpp" // Needs this to apply effects
#include <array>
#include <vector>

class World {
public:
  explicit World(Context context); // loadfrom context
  World(const World &) = delete;
  World &operator=(const World &) = delete;
  World(World &&) = delete;
  World &operator=(World &&) = delete;

  void update(sf::Time dt);
  void draw();

  bool hasReachedDestination() const;
  bool hasCrashed() const;

private:
  void handleCollisions();
  void buildScene();

private:
  Context mContext;
  sf::RenderWindow &mWindow;

  SceneNode mSceneGraph;
  std::array<SceneNode *, 3> mSceneLayers; // allows to make drawing layers

  PlayerCar *mPlayer;         // player
  MalusManager mMalusManager; // maluses
  std::vector<TrafficCar *> mTrafficCars;

  sf::FloatRect mWorldBounds; // limit bow of movement
  float mScrollSpeed;         // speed of thee game
};

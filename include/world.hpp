#pragma once
#include "Entities.hpp"
#include "MalusSystem.hpp" // Needs this to apply effects

class World : private sf::NonCopyable {
public:
  explicit World(Context context); // loadfrom context

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

  sf::FloatRect mWorldBounds; // limit bow of movement
  float mScrollSpeed;         // speed of thee game
};

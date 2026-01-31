#pragma once
#include "SharedContext.hpp"
#include <SFML/Graphics.hpp>
#include <array>
#include <memory> // <--- Added for unique_ptr
#include <tuple>  // <--- Added for std::tuple
#include <vector>

// Forward declaration
class PlayerCar;

class World : private sf::NonCopyable {
public:
  explicit World(Context context);
  ~World(); // <--- NEW: Explicit declaration (Promise to define it in .cpp)

  void update(sf::Time dt);
  void draw();

  // Check game over conditions
  bool hasCrashed() const;
  bool hasReachedDestination() const;

private:
  void handleCollisions();

private:
  Context mContext;
  sf::RenderWindow &mWindow;

  // Scene logic
  sf::View mWorldView;
  sf::FloatRect mWorldBounds;
  sf::Vector2f mSpawnPosition;
  float mScrollSpeed;

  // Game Objects
  // We use unique_ptr to manage memory automatically
  std::unique_ptr<PlayerCar> mPlayerCar;

  // The Road is visually just a rectangle in Jonas's code
  sf::RectangleShape mRoadRect;
  std::tuple<sf::Vector2f, sf::Vector2f> mRoadBorders; // Left/Right limits
};

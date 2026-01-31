#pragma once
#include "SharedContext.hpp"
#include <SFML/Graphics.hpp>

struct Command; // struct for command move right left etc

// Base class for maluses
class Malus {
public:
  virtual ~Malus() = default;

  // how the malus modify the inputs
  virtual void modifyInput(GameID::Action &action) {}

  // how the malus impacts the visuals
  virtual void applyScreenEffect(sf::RenderWindow &window) {}

  // modifies physics
  virtual float getSpeedMultiplier() const { return 1.0f; }

  // can add more effects of malusese here
};

// manage maluses for curretn sessions
class MalusManager {
public:
  // build maluses from session
  void loadFromSession(const SessionData &session);

  // add maluses effects to inputs
  GameID::Action processInput(GameID::Action rawInput);

  // get all visuals effects from amluses
  void drawEffects(sf::RenderWindow &window);

private:
  std::vector<std::unique_ptr<Malus>> mActiveEffects;
};

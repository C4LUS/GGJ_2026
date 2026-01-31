#pragma once
#include "State.hpp"
#include "World.hpp" // <--- Include World
#include <SFML/Graphics.hpp>

class DrivingState : public State {
public:
  DrivingState(StateStack &stack, Context context);

  virtual void draw() override;
  virtual bool update(sf::Time dt) override;
  virtual bool handleEvent(const sf::Event &event) override;

private:
  World mWorld; // <--- The Physics Engine
};

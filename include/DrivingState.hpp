#pragma once
#include "State.hpp"
#include "world.hpp"

class DrivingState : public State {
public:
  DrivingState(StateStack &stack, Context context);

  void draw() override;
  bool update(sf::Time dt) override;
  bool handleEvent(const sf::Event &event) override;

private:
  World mWorld;
};

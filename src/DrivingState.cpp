#include "../include/DrivingState.hpp"

DrivingState::DrivingState(StateStack &stack, Context context)
    : State(stack, context), mWorld(context) {}

void DrivingState::draw() { mWorld.draw(); }

bool DrivingState::update(sf::Time dt) {
  mWorld.update(dt);
  return true;
}

bool DrivingState::handleEvent(const sf::Event &event) {
  if (const auto *keyPressed = event.getIf<sf::Event::KeyPressed>()) {
    if (keyPressed->code == sf::Keyboard::Key::Escape) {
      requestStackPop();
    }
  }
  return true;
}

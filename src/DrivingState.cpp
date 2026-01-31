#include "../include/DrivingState.hpp"
#include "../include/GameId.hpp"

DrivingState::DrivingState(StateStack &stack, Context context)
    : State(stack, context), mWorld(context) // <--- Initialize World
{}

void DrivingState::draw() {
  mWorld.draw(); // Delegate to World
}

bool DrivingState::update(sf::Time dt) {
  mWorld.update(dt);
  return true;
}

bool DrivingState::handleEvent(const sf::Event &event) {
  // Pause Logic
  if (getContext().input->isActionTriggered(GameID::Action::Pause, event)) {
    requestStackPush(GameID::State::Pause);
  }
  return false;
}

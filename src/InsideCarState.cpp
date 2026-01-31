#include "../include/InsideCarState.hpp"
#include "../include/GameId.hpp"
#include <iostream>

InsideCarState::InsideCarState(StateStack &stack, Context context)
    : State(stack, context) {
  std::cout << "[Stack] Entered INSIDE CAR State (Blue Screen)" << std::endl;

  // Blue Background
  sf::RenderWindow &window = *getContext().window;
  mBackground.setSize(sf::Vector2f(window.getSize()));
  mBackground.setFillColor(sf::Color::Blue);
}

void InsideCarState::draw() { getContext().window->draw(mBackground); }

bool InsideCarState::update(sf::Time dt) { return true; }

bool InsideCarState::handleEvent(const sf::Event &event) {
  // If Pause/Back is pressed, go back to menu
  if (getContext().input->isActionTriggered(GameID::Action::Pause, event)) {
    std::cout << "[Input] Pause detected! Returning to Menu..." << std::endl;
    requestStackPop();
    requestStackPush(GameID::State::Menu);
  }
  return false;
}

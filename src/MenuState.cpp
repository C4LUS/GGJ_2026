#include "../include/MenuState.hpp"
#include "../include/GameId.hpp"
#include <iostream>

MenuState::MenuState(StateStack &stack, Context context)
    : State(stack, context) {
  std::cout << "[Stack] Entered MENU State (Red Screen)" << std::endl;

  sf::RenderWindow &window = *getContext().window;
  mBackground.setSize(sf::Vector2f(window.getSize()));
  mBackground.setFillColor(sf::Color::Red);
}

void MenuState::draw() {
  sf::RenderWindow &window = *getContext().window;
  window.draw(mBackground);
}

bool MenuState::update(sf::Time dt) { return true; }

bool MenuState::handleEvent(const sf::Event &event) {
  if (getContext().input->isActionTriggered(GameID::Action::Confirm, event)) {
    std::cout << "[Input] Confirm detected! Switching to InsideCar..."
              << std::endl;

    requestStackPop();
    requestStackPush(GameID::State::InsideCar);
  }
  return false;
}

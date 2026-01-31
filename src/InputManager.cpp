#include "../include/InputManager.hpp"

InputManager::InputManager() {
  bindKey(sf::Keyboard::Key::Left, GameID::Action::SteerLeft);
  bindKey(sf::Keyboard::Key::Right, GameID::Action::SteerRight);
  bindKey(sf::Keyboard::Key::Up, GameID::Action::Accelerate);
  bindKey(sf::Keyboard::Key::Down, GameID::Action::Brake);
}

void InputManager::bindKey(sf::Keyboard::Key key, GameID::Action action) {
  mKeyBinding.insert(std::make_pair(action, key));
}

bool InputManager::isActionActive(GameID::Action action) const {
  auto range = mKeyBinding.equal_range(action);
  for (auto it = range.first; it != range.second; ++it) {
    if (sf::Keyboard::isKeyPressed(it->second)) {
      return true;
    }
  }
  return false;
}

bool InputManager::isActionTriggered(GameID::Action action,
                                     const sf::Event &event) const {
  const auto *keyPressed = event.getIf<sf::Event::KeyPressed>();
  if (!keyPressed) {
    return false;
  }

  auto range = mKeyBinding.equal_range(action);
  for (auto it = range.first; it != range.second; ++it) {
    if (keyPressed->code == it->second) {
      return true;
    }
  }
  return false;
}

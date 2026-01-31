#include "../include/InputManager.hpp"

InputManager::InputManager() {
  // --- Default Bindings ---

  // Driving Controls (Arrows + WASD)
  bindKey(sf::Keyboard::Left, GameID::Action::SteerLeft);
  bindKey(sf::Keyboard::Q, GameID::Action::SteerLeft);

  bindKey(sf::Keyboard::Right, GameID::Action::SteerRight);
  bindKey(sf::Keyboard::D, GameID::Action::SteerRight);

  bindKey(sf::Keyboard::Up, GameID::Action::Accelerate);
  bindKey(sf::Keyboard::Z, GameID::Action::Accelerate);

  bindKey(sf::Keyboard::Down, GameID::Action::Brake);
  bindKey(sf::Keyboard::S, GameID::Action::Brake);

  // Menu / UI Controls
  bindKey(sf::Keyboard::Enter, GameID::Action::Confirm);
  bindMouse(sf::Mouse::Left, GameID::Action::Confirm);

  bindKey(sf::Keyboard::Escape, GameID::Action::Pause);
  bindKey(sf::Keyboard::P, GameID::Action::Pause);
}

void InputManager::bindKey(sf::Keyboard::Key key, GameID::Action action) {
  mKeyBinding.insert(std::make_pair(action, key));
}

void InputManager::bindMouse(sf::Mouse::Button button, GameID::Action action) {
  mMouseBinding.insert(std::make_pair(action, button));
}

bool InputManager::isActionActive(GameID::Action action) const {
  // 1. Check Keyboard bindings
  auto keyRange = mKeyBinding.equal_range(action);
  for (auto it = keyRange.first; it != keyRange.second; ++it) {
    if (sf::Keyboard::isKeyPressed(it->second))
      return true;
  }

  // 2. Check Mouse bindings
  auto mouseRange = mMouseBinding.equal_range(action);
  for (auto it = mouseRange.first; it != mouseRange.second; ++it) {
    if (sf::Mouse::isButtonPressed(it->second))
      return true;
  }

  return false;
}

bool InputManager::isActionTriggered(GameID::Action action,
                                     const sf::Event &event) const {
  // 1. Check Keyboard Events
  if (event.type == sf::Event::KeyPressed) {
    auto range = mKeyBinding.equal_range(action);
    for (auto it = range.first; it != range.second; ++it) {
      if (event.key.code == it->second)
        return true;
    }
  }

  // 2. Check Mouse Events
  if (event.type == sf::Event::MouseButtonPressed) {
    auto range = mMouseBinding.equal_range(action);
    for (auto it = range.first; it != range.second; ++it) {
      if (event.mouseButton.button == it->second)
        return true;
    }
  }

  return false;
}

sf::Vector2i
InputManager::getMousePosition(const sf::RenderWindow &window) const {
  return sf::Mouse::getPosition(window);
}

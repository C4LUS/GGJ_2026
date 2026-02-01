#include "../include/InputManager.hpp"

InputManager::InputManager() {
  // Driving Controls (Arrows + WASD/ZQSD for Azerty compatibility)
  bindKey(sf::Keyboard::Key::Left, GameID::Action::SteerLeft);
  bindKey(sf::Keyboard::Key::Q, GameID::Action::SteerLeft);
  bindKey(sf::Keyboard::Key::A, GameID::Action::SteerLeft);

  bindKey(sf::Keyboard::Key::Right, GameID::Action::SteerRight);
  bindKey(sf::Keyboard::Key::D, GameID::Action::SteerRight);

  bindKey(sf::Keyboard::Key::Up, GameID::Action::Accelerate);
  bindKey(sf::Keyboard::Key::Z, GameID::Action::Accelerate);
  bindKey(sf::Keyboard::Key::W, GameID::Action::Accelerate);

  bindKey(sf::Keyboard::Key::Down, GameID::Action::Brake);
  bindKey(sf::Keyboard::Key::S, GameID::Action::Brake);

  // Menu / UI Controls
  bindKey(sf::Keyboard::Key::Enter, GameID::Action::Confirm);
  bindMouse(sf::Mouse::Button::Left, GameID::Action::Confirm);

  bindKey(sf::Keyboard::Key::Escape, GameID::Action::Pause);
  bindKey(sf::Keyboard::Key::P, GameID::Action::Pause);
}

void InputManager::bindKey(sf::Keyboard::Key key, GameID::Action action) {
  mKeyBinding.insert(std::make_pair(action, key));
}

void InputManager::bindMouse(sf::Mouse::Button button, GameID::Action action) {
  mMouseBinding.insert(std::make_pair(action, button));
}

bool InputManager::isActionActive(GameID::Action action) const {
  auto keyRange = mKeyBinding.equal_range(action);
  for (auto it = keyRange.first; it != keyRange.second; ++it) {
    if (sf::Keyboard::isKeyPressed(it->second)) {
      return true;
    }
  }

  auto mouseRange = mMouseBinding.equal_range(action);
  for (auto it = mouseRange.first; it != mouseRange.second; ++it) {
    if (sf::Mouse::isButtonPressed(it->second)) {
      return true;
    }
  }
  return false;
}

bool InputManager::isActionTriggered(GameID::Action action,
                                     const sf::Event &event) const {
  if (const auto *keyPressed = event.getIf<sf::Event::KeyPressed>()) {
    auto range = mKeyBinding.equal_range(action);
    for (auto it = range.first; it != range.second; ++it) {
      if (keyPressed->code == it->second) {
        return true;
      }
    }
  }

  if (const auto *mousePressed =
          event.getIf<sf::Event::MouseButtonPressed>()) {
    auto range = mMouseBinding.equal_range(action);
    for (auto it = range.first; it != range.second; ++it) {
      if (mousePressed->button == it->second) {
        return true;
      }
    }
  }
  return false;
}

sf::Vector2i
InputManager::getMousePosition(const sf::RenderWindow &window) const {
  return sf::Mouse::getPosition(window);
}

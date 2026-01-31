#pragma once
#include "GameId.hpp"
#include <SFML/Window.hpp>
#include <map>
#include <vector>

class InputManager {
public:
  InputManager();

  // Configuration: Assign a key to an action (e.g., 'A' -> SteerLeft)
  void bindKey(sf::Keyboard::Key key, GameID::Action action);

  // Real-time Check: "Is the button for 'SteerLeft' currently held down?"
  bool isActionActive(GameID::Action action) const;

  // Event Check: "Did the button for 'Pause' just get pressed?"
  // Useful for Menus to avoid repeat-firing
  bool isActionTriggered(GameID::Action action, const sf::Event &event) const;

private:
  // We use a multimap because one action might have multiple keys
  // (e.g., Arrows AND WASD)
  std::multimap<GameID::Action, sf::Keyboard::Key> mKeyBinding;
};

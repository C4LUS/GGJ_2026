#pragma once
#include "GameId.hpp"
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>

class InputManager {
public:
  InputManager();

  // Configuration: Assign a key to an action (e.g., 'A' -> SteerLeft)
  void bindKey(sf::Keyboard::Key key, GameID::Action action);
  void bindMouse(sf::Mouse::Button button, GameID::Action action);

  // Real-time Check: "Is the button for 'SteerLeft' currently held down?"
  bool isActionActive(GameID::Action action) const;

  // Event Check: "Did the button for 'Pause' just get pressed?"
  // Useful for Menus to avoid repeat-firing
  bool isActionTriggered(GameID::Action action, const sf::Event &event) const;

  // Helper to get mouse position relative to a window
  sf::Vector2i getMousePosition(const sf::RenderWindow &window) const;

private:
  // We use a multimap because one action might have multiple keys
  // (e.g., Arrows AND WASD)
  std::multimap<GameID::Action, sf::Keyboard::Key> mKeyBinding;
  std::multimap<GameID::Action, sf::Mouse::Button> mMouseBinding;
};

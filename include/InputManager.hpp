#pragma once
#include "GameId.hpp"
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>

class InputManager {
public:
  InputManager();

  // Configuration
  void bindKey(sf::Keyboard::Key key, GameID::Action action);
  void bindMouse(sf::Mouse::Button button, GameID::Action action);

  // Real-time Check (Held down - for Driving)
  bool isActionActive(GameID::Action action) const;

  // Event Check (Pressed once - for Menus/Phone)
  bool isActionTriggered(GameID::Action action, const sf::Event &event) const;

  // Helper to get mouse position relative to a window
  sf::Vector2i getMousePosition(const sf::RenderWindow &window) const;

private:
  std::multimap<GameID::Action, sf::Keyboard::Key> mKeyBinding;
  std::multimap<GameID::Action, sf::Mouse::Button> mMouseBinding;
};

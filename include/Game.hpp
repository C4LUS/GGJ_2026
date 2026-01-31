#pragma once
#include "Assets.hpp" // <--- Include this
#include "SharedContext.hpp"
#include "StateStack.hpp"
#include <SFML/Graphics.hpp>

class Game {
public:
  Game();
  void run();

private:
  void processInput();
  void update(sf::Time dt);
  void render();

  void registerStates();

private:
  sf::RenderWindow mWindow;
  Assets mAssets; // <--- CHANGED: Owns the centralized assets
  InputManager mInputManager;
  SessionData mSession;
  StateStack mStateStack;
};

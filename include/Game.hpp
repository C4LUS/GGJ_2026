#pragma once
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
  TextureHolder mTextures;
  FontHolder mFonts;
  InputManager mInputManager; // manage the inputs
  SessionData mSession;       // The session infos (score, masks etc)

  StateStack mStateStack; // accumulation of state, push running, push menu
                          // mode, pop menu to return to game
};

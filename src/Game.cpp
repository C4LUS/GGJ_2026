#include "../include/Game.hpp"
#include "../include/InsideCarState.hpp"
#include "../include/MenuState.hpp"
#include <optional>

const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
    : mWindow(sf::VideoMode({1280u, 720u}), "Masked Delivery (Stack Test)",
              sf::Style::Close),
      mTextures(), mFonts(), mInputManager(), mSession(),
      mStateStack({&mWindow, &mTextures, &mFonts, &mInputManager, &mSession}) {
  mWindow.setKeyRepeatEnabled(false);
  registerStates();

  // Start at Menu
  mStateStack.pushState(GameID::State::Menu);
}

void Game::run() {
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;

  while (mWindow.isOpen()) {
    sf::Time dt = clock.restart();
    timeSinceLastUpdate += dt;

    while (timeSinceLastUpdate > TimePerFrame) {
      timeSinceLastUpdate -= TimePerFrame;
      processInput();
      update(TimePerFrame);

      if (mStateStack.isEmpty())
        mWindow.close();
    }
    render();
  }
}

void Game::processInput() {
  while (const std::optional event = mWindow.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      mWindow.close();
    }

    mStateStack.handleEvent(*event);
  }
}

void Game::update(sf::Time dt) { mStateStack.update(dt); }

void Game::render() {
  mWindow.clear();
  mStateStack.draw();
  mWindow.display();
}

void Game::registerStates() {
  mStateStack.registerState<MenuState>(GameID::State::Menu);
  mStateStack.registerState<InsideCarState>(GameID::State::InsideCar);
}

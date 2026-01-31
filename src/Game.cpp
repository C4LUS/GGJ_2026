#include "../include/Game.hpp"
#include <iostream>
#include <optional>

namespace {
class TestState final : public State {
public:
  TestState(StateStack &stack, Context context)
      : State(stack, context) {
    mBlock.setSize(sf::Vector2f(240.f, 120.f));
    mBlock.setFillColor(sf::Color(30, 200, 130));
    mBlock.setPosition({40.f, 40.f});
  }

  void draw() override {
    if (auto *window = getContext().window) {
      window->draw(mBlock);
    }
  }

  bool update(sf::Time dt) override {
    return true;
  }

  bool handleEvent(const sf::Event &event) override {
    if (const auto *keyPressed = event.getIf<sf::Event::KeyPressed>()) {
      if (keyPressed->code == sf::Keyboard::Key::Escape) {
        requestStackPop();
      }
    }
    return true;
  }

private:
  sf::RectangleShape mBlock;
};
} // namespace

const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
    : mWindow(sf::VideoMode({1280u, 720u}), "RaMask moi", sf::Style::Close),
      mTextures(), mFonts(), mInputManager(), mSession(),
      mStateStack({&mWindow, &mTextures, &mFonts, &mInputManager, &mSession}) {
  mWindow.setKeyRepeatEnabled(false);
  registerStates();

  // Start with the Menu
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
  // Include specific State headers here
  mStateStack.registerState<TestState>(GameID::State::Menu);
  // mStateStack.registerState<InsideCarState>(GameID::State::InsideCar);
  // mStateStack.registerState<DrivingState>(GameID::State::Driving);
}

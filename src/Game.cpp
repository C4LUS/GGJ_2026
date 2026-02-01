#include "../include/Game.hpp"
#include "../include/BlurEffect.hpp"
#include "../include/DrivingState.hpp"
#include "../include/GrayscaleEffect.hpp"
#include "../include/InsideCarState.hpp"
#include "../include/MenuState.hpp"
#include "../include/MixedControlsEffect.hpp"
#include "../include/ReverseEffect.hpp"
#include "../include/ScreenShakeEffect.hpp"
#include "../include/SplitEffect.hpp"
#include "../include/WaveDistortionEffect.hpp"

const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
    : mWindow(sf::VideoMode(1280, 720), "Masked Delivery", sf::Style::Close),
      mAssets(), // <--- NEW: Initialize the centralized Assets
      mInputManager(), mSession(),
      // <--- NEW: Context now takes 4 arguments: Window, Assets, Input, Session
      mStateStack({&mWindow, &mAssets, &mInputManager, &mSession}) {
  mWindow.setKeyRepeatEnabled(false);
  registerStates();

  // Configure effect chain and malus giver in one place
  auto &chain = mSession.effectChain;
  // Mapping: Alcool->wave, Fat->shake, Coke->mixedcontrols,
  // Stinky->grayscale, Headset->blur
  chain.addEffect(GameID::Malus::Alcool,
                  std::make_unique<WaveDistortionEffect>(8.f, 0.06f, 2.f, "wave"));
  chain.addEffect(GameID::Malus::Stinky,
                  std::make_unique<GrayscaleEffect>(20.0f, "grayscale"));
  chain.addEffect(GameID::Malus::Headset,
                  std::make_unique<BlurEffect>(2.0f, "blur"));
  chain.addEffect(GameID::Malus::MixedControls,
                  std::make_unique<MixedControlsEffect>(mInputManager, "mixedcontrols"));
  chain.addEffect(GameID::Malus::Reverse,
                  std::make_unique<ReverseEffect>("reverse"));
  chain.addEffect(GameID::Malus::Split,
                  std::make_unique<SplitEffect>("split"));
  chain.addEffect(GameID::Malus::Fat,
                  std::make_unique<ScreenShakeEffect>(24.f, 8.f, 2.f, "shake"));
  chain.setAllDisabled();

  mSession.malusGiver.setHandler(MalusGiver::Wave,
                                [&chain]() { chain.setEnabled(GameID::Malus::Alcool, true); });
  mSession.malusGiver.setHandler(MalusGiver::Grayscale,
                                [&chain]() { chain.setEnabled(GameID::Malus::Stinky, true); });
  mSession.malusGiver.setHandler(MalusGiver::Blur,
                                [&chain]() { chain.setEnabled(GameID::Malus::Headset, true); });
  mSession.malusGiver.setHandler(MalusGiver::MixedControls,
                                [&chain]() { chain.setEnabled(GameID::Malus::MixedControls, true); });
  mSession.malusGiver.setHandler(MalusGiver::Reverse,
                                [&chain]() { chain.setEnabled(GameID::Malus::Reverse, true); });
  mSession.malusGiver.setHandler(MalusGiver::Split,
                                [&chain]() { chain.setEnabled(GameID::Malus::Split, true); });
  mSession.malusGiver.setHandler(MalusGiver::Shake,
                                [&chain]() { chain.setEnabled(GameID::Malus::Fat, true); });

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
  sf::Event event;
  while (mWindow.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      mWindow.close();

    mStateStack.handleEvent(event);
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
  mStateStack.registerState<DrivingState>(
      GameID::State::Driving); // <--- UNCOMMENT THIS
}

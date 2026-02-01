#include "../include/DrivingState.hpp"
#include "../include/GameId.hpp"
#include "../include/MalusGiver.hpp"
#include <random>

DrivingState::DrivingState(StateStack &stack, Context context)
    : State(stack, context), mWorld(context) // <--- Initialize World
{
  enableEffectChain();
}

DrivingState::~DrivingState() {
  disableEffectChain();
}

void DrivingState::draw() {
  mWorld.draw(); // Delegate to World
}

bool DrivingState::update(sf::Time dt) {
  mWorld.update(dt);
  return true;
}

bool DrivingState::handleEvent(const sf::Event &event) {
  // Pause Logic
  if (getContext().input->isActionTriggered(GameID::Action::Pause, event)) {
    disableEffectChain();
    requestStackPush(GameID::State::Pause);
  }

  if (event.type == sf::Event::KeyPressed && getContext().session) {
    std::cout << "Key pressed: " << event.key.code << std::endl;
    auto &giver = getContext().session->malusGiver;
    switch (event.key.code) {
    case sf::Keyboard::C:
      if (mEffectsEnabled) {
        disableEffectChain();
      } else {
        enableEffectChain();
        getContext().session->effectChain.setAllEnabled();
      }
      break;
    case sf::Keyboard::Space:
      giver.run();
      break;
    case sf::Keyboard::Num1:
      giver.add(MalusGiver::Wave, 1);
      break;
    case sf::Keyboard::Num2:
      giver.add(MalusGiver::Grayscale, 1);
      break;
    case sf::Keyboard::Num3:
      giver.add(MalusGiver::Blur, 1);
      break;
    case sf::Keyboard::Num7: // Num4 doesn't work on my keyboard :/
      {
        static std::mt19937 rng{std::random_device{}()};
        std::uniform_int_distribution<int> dist(0, 2);
        int choice = dist(rng);
        if (choice == 0) {
          std::cout << "Adding SPLIT Effect\n" << std::endl;
          giver.add(MalusGiver::Split, 1);
        } else if (choice == 1) {
          std::cout << "Adding REVERSE Effect\n" << std::endl;
          giver.add(MalusGiver::Reverse, 1);
        } else {
          std::cout << "Adding MIXED Effect\n" << std::endl;
          giver.add(MalusGiver::MixedControls, 1);
        }
      }
      break;
    case sf::Keyboard::Num5:
      giver.add(MalusGiver::Shake, 1);
      break;
    default:
      break;
    }
  }
  return false;
}

void DrivingState::enableEffectChain() {
  if (mEffectsEnabled) return;
  mEffectsEnabled = true;
}

void DrivingState::disableEffectChain() {
  if (!mEffectsEnabled) return;
  mEffectsEnabled = false;
  if (getContext().session) {
    getContext().session->effectChain.setAllDisabled();
  }
}

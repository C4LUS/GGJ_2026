#include "../include/MalusSystem.hpp"

void MalusManager::loadFromSession(const SessionData &session) {
  mActiveEffects.clear();

  // TODO: instantiate concrete Malus types based on session.activeMaluses.
  (void)session;
}

GameID::Action MalusManager::processInput(GameID::Action rawInput) {
  GameID::Action result = rawInput;
  for (const auto &effect : mActiveEffects) {
    effect->modifyInput(result);
  }
  return result;
}

void MalusManager::drawEffects(sf::RenderWindow &window) {
  for (const auto &effect : mActiveEffects) {
    effect->applyScreenEffect(window);
  }
}

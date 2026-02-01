#pragma once
#include "Assets.hpp"
#include "GameId.hpp" // <--- Include Enums from here
#include "FrameEffect.hpp" // For EffectChain
#include "InputManager.hpp"
#include "MalusGiver.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

// Current run data
struct SessionData {
  int currentDay = 1;
  float cash = 0.0f;

  // The active effects chain for rendering malus effects
  EffectChain effectChain;

  // Centralized malus giver (configured in Game constructor)
  MalusGiver malusGiver;

  // The Mask currently equipped (This is of type Malus because it protects
  // against that specific Malus) Logic: If activeMaluses contains
  // Malus::Alcool, but currentMask == Malus::Alcool, the effect is blocked.
  GameID::Malus currentMask = GameID::Malus::None;

  // The Threat detected in the Office Phase (used to check success/fail later)
  GameID::Malus requiredMaskForNextRun = GameID::Malus::None;
};

// Tool box passed to every state
struct Context {
  sf::RenderWindow *window;
  Assets *assets;
  InputManager *input;
  SessionData *session;
};

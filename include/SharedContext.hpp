#pragma once
#include "Assets.hpp"
#include "GameId.hpp" // <--- Include Enums from here
#include "InputManager.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

// Current run data
struct SessionData {
  int currentDay = 1;
  float cash = 0.0f;

  // The Maluses currently active on the player (e.g., {Malus::Alcool,
  // Malus::Fat})
  std::vector<GameID::Malus> activeMaluses;

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

#pragma once
#include "InputManager.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

// Current run data
struct SessionData {
  int currentDay = 1;
  float cash = 0.0f;

  // Accumulation of maluses
  std::vector<GameID::Malus> activeMaluses;

  // Current equiped mask
  GameID::Malus currentMalus = GameID::Malus::None;

  // Required mask to be protected
  GameID::Malus requiredMalusForNextRun = GameID::Malus::None;
};

// Template to manage ressources: sound, texture, font etc
template <typename Resource, typename Identifier> class ResourceHolder {
  // to add: map<Identifier, unique_ptr<Resource>>
public:
  void load(Identifier id, const std::string &filename);
  Resource &get(Identifier id);
  const Resource &get(Identifier id) const;
};

typedef ResourceHolder<sf::Texture, GameID::Texture> TextureHolder;
typedef ResourceHolder<sf::Font, GameID::Font> FontHolder;

// tool box to allow all sections to work with the game
struct Context {
  sf::RenderWindow *window;
  TextureHolder *textures;
  FontHolder *fonts;
  InputManager *input;
  SessionData *session;
};

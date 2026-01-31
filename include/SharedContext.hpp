#pragma once
#include "InputManager.hpp"
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
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
public:
  void load(Identifier id, const std::string &filename);
  Resource &get(Identifier id);
  const Resource &get(Identifier id) const;

private:
  std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
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

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id,
                                                const std::string &filename) {
  auto resource = std::make_unique<Resource>();
  if (!resource->loadFromFile(filename)) {
    throw std::runtime_error("ResourceHolder: failed to load " + filename);
  }

  auto inserted = mResourceMap.emplace(id, std::move(resource));
  if (!inserted.second) {
    throw std::runtime_error("ResourceHolder: duplicate resource id");
  }
}

template <typename Resource, typename Identifier>
Resource &ResourceHolder<Resource, Identifier>::get(Identifier id) {
  auto found = mResourceMap.find(id);
  if (found == mResourceMap.end()) {
    throw std::runtime_error("ResourceHolder: resource id not found");
  }
  return *found->second;
}

template <typename Resource, typename Identifier>
const Resource &ResourceHolder<Resource, Identifier>::get(Identifier id) const {
  auto found = mResourceMap.find(id);
  if (found == mResourceMap.end()) {
    throw std::runtime_error("ResourceHolder: resource id not found");
  }
  return *found->second;
}

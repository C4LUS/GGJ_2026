#pragma once
#include "SharedContext.hpp"
#include <SFML/Graphics.hpp>

// The Phone Logic
class PhoneSystem : public sf::Drawable {
public:
  PhoneSystem(const TextureHolder &textures);

  void update(sf::Time dt);
  void triggerCall(int difficultyLevel);

  // choose mask after call
  bool handleEvent(const sf::Event &event, const sf::RenderWindow &window);

  // get the usefull mask
  GameID::Mask getRequiredMask() const;

private:
  enum State { Idle, Ringing, Talking, Finished };
  State mState;
  sf::Sprite mSprite;
  sf::Text mSubtitleText;
};

// mask select
class MaskSelector : public sf::Drawable {
public:
  MaskSelector(Context context);

  void handleEvent(const sf::Event &event);
  GameID::Mask getSelectedMask() const;

private:
  struct Button {
    sf::Sprite sprite;
    GameID::Mask maskID;
    bool isSelected;
  };
  std::vector<Button> mButtons;
};

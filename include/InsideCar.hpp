#pragma once
#include "SharedContext.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

// The Phone Logic
class PhoneSystem : public sf::Drawable {
public:
  PhoneSystem(const TextureHolder &textures);

  void update(sf::Time dt);

  // choose mask after call
  bool handleEvent(const sf::Event &event, const sf::RenderWindow &window);

  // get the usefull mask
  GameID::Malus getRequiredMask() const;
  bool isWaitingForMask() const;
  bool isCallFinished() const;
  void reset();

private:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  enum State { Idle, Ringing, Talking, Finished };
  State mState;
  GameID::Malus mRequiredMask;
  sf::Time time;
  sf::Sprite mSprite;
  sf::Text mSubtitleText;
};

// mask select
class MaskSelector : public sf::Drawable {
public:
  MaskSelector(Context context);

  void handleEvent(const sf::Event &event);
  GameID::Malus getSelectedMask() const;
  void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
  struct Button {
    sf::Sprite sprite;
    GameID::Malus maskID;
    bool isSelected;
  };
  std::vector<Button> mButtons;
};

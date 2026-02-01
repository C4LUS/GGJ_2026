#pragma once
#include "InsideCar.hpp" // Include the components
#include "State.hpp"
#include <SFML/Graphics.hpp>

class InsideCarState : public State {
public:
  InsideCarState(StateStack &stack, Context context);

  virtual void draw() override;
  virtual bool update(sf::Time dt) override;
  virtual bool handleEvent(const sf::Event &event) override;

private:
  sf::RectangleShape mBackground;
  sf::Text mInfoText;

  // Components
  PhoneSystem mPhoneSystem;
  MaskSelector mMaskSelector;
};

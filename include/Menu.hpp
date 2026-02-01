#pragma once
#include "State.hpp"
#include <SFML/Graphics.hpp>

class MenuState : public State {
public:
  MenuState(StateStack &stack, Context context);

  virtual void draw() override;
  virtual bool update(sf::Time dt) override;
  virtual bool handleEvent(const sf::Event &event) override;

private:
  sf::Text mTitleText;
  sf::Text mPromptText;
  sf::RectangleShape mBackground;
};

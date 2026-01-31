#pragma once
#include "GameId.hpp"
#include "SharedContext.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class StateStack;

class State {
public:
  typedef std::unique_ptr<State> Ptr;

  // Constructor needs Context and the stack (to request pushes/pops)
  State(StateStack &stack, Context context);
  virtual ~State() = default;

  virtual void draw() = 0;
  virtual bool update(sf::Time dt) = 0;
  virtual bool handleEvent(const sf::Event &event) = 0;

protected:
  // Helper function to ask the stack to change states
  void requestStackPush(GameID::State stateID);
  void requestStackPop();
  void requestStateClear();

  Context getContext() const;

private:
  StateStack *mStack;
  Context mContext;
};

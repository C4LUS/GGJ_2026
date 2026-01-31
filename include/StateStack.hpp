#pragma once
#include "GameId.hpp"
#include "State.hpp"
#include <SFML/Graphics.hpp>
#include <functional>
#include <map>
#include <vector>

class StateStack {
public:
  enum class Action { Push, Pop, Clear };

  explicit StateStack(Context context);
  StateStack(const StateStack &) = delete;
  StateStack &operator=(const StateStack &) = delete;
  StateStack(StateStack &&) = delete;
  StateStack &operator=(StateStack &&) = delete;

  template <typename T> void registerState(GameID::State stateID);

  void update(sf::Time dt);
  void draw();
  void handleEvent(const sf::Event &event);

  void pushState(GameID::State stateID);
  void popState();
  void clearStates();

  bool isEmpty() const;

private:
  struct PendingChange {
    Action action;
    GameID::State stateID;
  };

  // Applies the changes (Push/Pop) only at the start of the frame
  // to avoid crashing if a state pops itself while updating.
  void applyPendingChanges();
  State::Ptr createState(GameID::State stateID);

private:
  std::vector<State::Ptr> mStack;
  std::vector<PendingChange> mPendingList;
  Context mContext;

  // Factory map: Knows how to create a "MenuState" when "State::Menu"
  std::map<GameID::State, std::function<State::Ptr()>> mFactories;
};

// Template implementation for registering states
template <typename T> void StateStack::registerState(GameID::State stateID) {
  mFactories[stateID] = [this]() { return State::Ptr(new T(*this, mContext)); };
}

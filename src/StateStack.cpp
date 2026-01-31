#include "../include/StateStack.hpp"
#include <cassert>

StateStack::StateStack(Context context)
    : mStack(), mPendingList(), mContext(context), mFactories() {}

void StateStack::update(sf::Time dt) {
  if (!mStack.empty()) {
    mStack.back()->update(dt);
  }
  applyPendingChanges();
}

void StateStack::draw() {
  // draw from bottom to top
  for (auto &state : mStack) {
    state->draw();
  }
}

void StateStack::handleEvent(const sf::Event &event) {
  // only the top state handles input
  if (!mStack.empty()) {
    mStack.back()->handleEvent(event);
  }
  applyPendingChanges();
}

void StateStack::pushState(GameID::State stateID) {
  mPendingList.push_back(PendingChange{Action::Push, stateID});
}

void StateStack::popState() {
  mPendingList.push_back(PendingChange{Action::Pop, GameID::State::None});
}

void StateStack::clearStates() {
  mPendingList.push_back(PendingChange{Action::Clear, GameID::State::None});
}

bool StateStack::isEmpty() const { return mStack.empty(); }

State::Ptr StateStack::createState(GameID::State stateID) {
  auto found = mFactories.find(stateID);
  assert(found != mFactories.end()); // crash if state not registered
  return found->second();
}

void StateStack::applyPendingChanges() {
  for (const auto &change : mPendingList) {
    switch (change.action) {
    case Action::Push:
      mStack.push_back(createState(change.stateID));
      break;
    case Action::Pop:
      if (!mStack.empty())
        mStack.pop_back();
      break;
    case Action::Clear:
      mStack.clear();
      break;
    }
  }
  mPendingList.clear();
}

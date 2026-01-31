#include "../include/State.hpp"
#include "../include/StateStack.hpp"

State::State(StateStack &stack, Context context) : mStack(&stack), mContext(context) {}

void State::requestStackPush(GameID::State stateID) {
  mStack->pushState(stateID);
}

void State::requestStackPop() { mStack->popState(); }

void State::requestStateClear() { mStack->clearStates(); }

Context State::getContext() const { return mContext; }

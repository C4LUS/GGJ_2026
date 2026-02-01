#include "../include/MixedControlsEffect.hpp"
#include <algorithm>

void MixedControlsEffect::onEnable() {
    if (mActive) return;
    mActive = true;
    mOriginalKeys = mInput.getKeyBindings();
    mOriginalMouse = mInput.getMouseBindings();
    shuffleBindings();
}

void MixedControlsEffect::onDisable() {
    if (!mActive) return;
    mActive = false;
    mInput.setKeyBindings(mOriginalKeys);
    mInput.setMouseBindings(mOriginalMouse);
}

void MixedControlsEffect::shuffleBindings() {
    // Only shuffle movement controls: SteerLeft, SteerRight, Accelerate, Brake
    std::vector<GameID::Action> movementActions = {
        GameID::Action::SteerLeft,
        GameID::Action::SteerRight,
        GameID::Action::Accelerate,
        GameID::Action::Brake
    };
    
    // Extract only movement control keys from original bindings
    std::vector<sf::Keyboard::Key> movementKeys;
    for (const auto &pair : mOriginalKeys) {
        if (std::find(movementActions.begin(), movementActions.end(), pair.first) != movementActions.end()) {
            movementKeys.push_back(pair.second);
        }
    }

    // Shuffle the movement keys
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(movementKeys.begin(), movementKeys.end(), gen);

    // Build new key bindings: keep non-movement controls, shuffle movement controls
    std::multimap<GameID::Action, sf::Keyboard::Key> newKeys;
    size_t keyIndex = 0;
    
    for (const auto &pair : mOriginalKeys) {
        bool isMovement = std::find(movementActions.begin(), movementActions.end(), pair.first) != movementActions.end();
        if (isMovement) {
            newKeys.insert(std::make_pair(pair.first, movementKeys[keyIndex++]));
        } else {
            newKeys.insert(std::make_pair(pair.first, pair.second));
        }
    }
    mInput.setKeyBindings(newKeys);

    // Don't shuffle mouse bindings - keep them as-is for non-movement controls
}

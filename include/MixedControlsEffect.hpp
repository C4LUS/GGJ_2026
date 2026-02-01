#ifndef MIXED_CONTROLS_EFFECT_HPP
#define MIXED_CONTROLS_EFFECT_HPP

#include "FrameEffect.hpp"
#include "InputManager.hpp"
#include <random>
#include <vector>

// Mixes input bindings randomly while enabled, restores original bindings when disabled.
class MixedControlsEffect : public FrameEffect {
public:
    explicit MixedControlsEffect(InputManager &input, const std::string &name = "mixedcontrols")
        : FrameEffect(name), mInput(input) {}

    void apply(const sf::Image &src, sf::Image &dst, float time = 0.f) override {
        (void)time;
        dst = src; // No visual change
    }

    void onEnable() override;
    void onDisable() override;

private:
    InputManager &mInput;
    bool mActive{false};
    std::multimap<GameID::Action, sf::Keyboard::Key> mOriginalKeys;
    std::multimap<GameID::Action, sf::Mouse::Button> mOriginalMouse;

    void shuffleBindings();
};

#endif

#pragma once
#include "FrameEffect.hpp"
#include <string>

class ReverseEffect : public FrameEffect {
public:
    ReverseEffect(const std::string& name = "reverse") : FrameEffect(name) {}
    void apply(const sf::Image& src, sf::Image& out, float t) override;
};

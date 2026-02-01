#pragma once
#include "FrameEffect.hpp"
#include <string>

class SplitEffect : public FrameEffect {
public:
    SplitEffect(const std::string& name = "split") : FrameEffect(name) {}
    void apply(const sf::Image& src, sf::Image& out, float t) override;
};

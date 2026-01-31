#ifndef BLUR_EFFECT_HPP
#define BLUR_EFFECT_HPP

#include "FrameEffect.hpp"
#include <vector>

// Simple box blur effect, intensity controls blur radius
class BlurEffect : public FrameEffect {
public:
    BlurEffect(float intensity = 1.0f, const std::string& name = "blur")
        : FrameEffect(name), intensity(intensity) {}

    void setIntensity(float i) { intensity = i; }
    float getIntensity() const { return intensity; }

    void apply(const sf::Image& src, sf::Image& dst, float time = 0.f) override;

private:
    float intensity{1.0f}; // Blur radius in pixels
};

#endif

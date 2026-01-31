#ifndef GRAYSCALE_EFFECT_FIXED_HPP
#define GRAYSCALE_EFFECT_FIXED_HPP

#include "FrameEffect.hpp"
#include <algorithm>
#include <string>

class GrayscaleEffect : public FrameEffect {
public:
    // intensity in [0,1] where 1 is full grayscale
    explicit GrayscaleEffect(float intensity = 1.f, const std::string& name = "grayscale")
        : FrameEffect(name), intensity(intensity) {}

    void setIntensity(float i) { intensity = std::clamp(i, 0.f, 1.f); }
    float getIntensity() const { return intensity; }

    // Helpers to tweak intensity incrementally
    void increaseIntensity(float step = 0.1f) { setIntensity(intensity + step); }
    void decreaseIntensity(float step = 0.1f) { setIntensity(intensity - step); }

    void apply(const sf::Image& src, sf::Image& dst, float time = 0.f) override;

private:
    float intensity{1.f};
};

#endif // GRAYSCALE_EFFECT_FIXED_HPP

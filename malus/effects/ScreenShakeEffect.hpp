#ifndef SCREEN_SHAKE_EFFECT_HPP
#define SCREEN_SHAKE_EFFECT_HPP

#include "FrameEffect.hpp"
#include <random>

// Shakes the screen sides horizontally like a car ride
class ScreenShakeEffect : public FrameEffect {
public:
    ScreenShakeEffect(float amplitude = 8.f, float frequency = 8.f, float speed = 1.f, const std::string& name = "shake")
        : FrameEffect(name), amplitude(amplitude), frequency(frequency), speed(speed) {}

    void setAmplitude(float a) { amplitude = a; }
    void setFrequency(float f) { frequency = f; }
    void setSpeed(float s) { speed = s; }

    void apply(const sf::Image& src, sf::Image& dst, float time = 0.f) override;

private:
    float amplitude{8.f};
    float frequency{8.f};
    float speed{1.f};
};

#endif

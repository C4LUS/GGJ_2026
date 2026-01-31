#ifndef WAVE_DISTORTION_EFFECT_HPP
#define WAVE_DISTORTION_EFFECT_HPP

#include "FrameEffect.hpp"

// Simple horizontal sine-wave distortion. Samples from source with x offset
class WaveDistortionEffect : public FrameEffect {
    public:
        WaveDistortionEffect(float amplitude = 10.f, float frequency = 0.05f, float speed = 1.f, const std::string& name = "wave")
            : FrameEffect(name), amplitude(amplitude), frequency(frequency), speed(speed) {}

        void setAmplitude(float a) { amplitude = a; }
        void setFrequency(float f) { frequency = f; }
        void setSpeed(float s) { speed = s; }

        void apply(const sf::Image& src, sf::Image& dst, float time = 0.f) override;

    private:
        float amplitude{10.f};
        float frequency{0.05f};
        float speed{1.f};
};

#endif

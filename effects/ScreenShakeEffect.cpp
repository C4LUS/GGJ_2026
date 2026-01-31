#include "ScreenShakeEffect.hpp"
#include <cmath>

static inline unsigned clampu(int v, unsigned max) {
    if (v < 0) return 0;
    if ((unsigned)v >= max) return max - 1;
    return (unsigned)v;
}

void ScreenShakeEffect::apply(const sf::Image& src, sf::Image& dst, float time) {
    sf::Vector2u s = src.getSize();
    dst.create(s.x, s.y, sf::Color::Transparent);

    // Simulate a heavy object entering: less aggressive, with balancing (pivot) from the center
    static std::default_random_engine rng;
    static std::normal_distribution<float> dist(0.f, 1.f);

    float t = time * speed;
    // Gentle sway (pivot) around the center, plus mild random shake
    // Smoother, less aggressive shake: lower amplitude, lower random, more sine
    float sway = std::sin(t * (frequency * 0.35f)) * amplitude * 0.5f;
    // Use a very small, smoothed random offset
    static float lastRand = 0.f;
    float targetRand = dist(rng) * amplitude * 0.02f;
    lastRand = lastRand * 0.9f + targetRand * 0.1f; // smooth the random
    float totalShake = sway + lastRand;

    // Add a balancing effect: rows above and below the center move in opposite directions
    float centerY = (s.y - 1) / 2.0f;
    for (unsigned y = 0; y < s.y; ++y) {
        float rel = (y - centerY) / centerY; // -1 at top, 0 at center, 1 at bottom
        // Clamp rel to [-1, 1] to avoid any floating point issues
        if (rel < -1.f) rel = -1.f;
        if (rel > 1.f) rel = 1.f;
        float balance = -rel * sway * 1.0f; // slightly less pivot
        float shake = totalShake + balance;
        for (unsigned x = 0; x < s.x; ++x) {
            int sampleX = static_cast<int>(std::round(x + shake));
            unsigned sx = clampu(sampleX, s.x);
            sf::Color c = src.getPixel(sx, y);
            dst.setPixel(x, y, c);
        }
    }
}

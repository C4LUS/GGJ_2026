#include "WaveDistortionEffect.hpp"
#include <cmath>

static inline unsigned clampu(int v, unsigned max) {
    if (v < 0) return 0;
    if ((unsigned)v >= max) return max - 1;
    return (unsigned)v;
}

void WaveDistortionEffect::apply(const sf::Image& src, sf::Image& dst, float time) {
    sf::Vector2u s = src.getSize();
    dst.create(s.x, s.y, sf::Color::Transparent);

    float t = time * speed;
    for (unsigned y = 0; y < s.y; ++y) {
        float shift = std::sin((y * frequency) + t) * amplitude;
        for (unsigned x = 0; x < s.x; ++x) {
            int sampleX = static_cast<int>(std::round(x + shift));
            unsigned sx = clampu(sampleX, s.x);
            sf::Color c = src.getPixel(sx, y);
            dst.setPixel(x, y, c);
        }
    }
}

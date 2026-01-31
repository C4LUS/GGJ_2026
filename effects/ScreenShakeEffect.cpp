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

    float t = time * speed;
    for (unsigned y = 0; y < s.y; ++y) {
        // Shake is stronger at the sides, less in the center
        float edgeFactor = std::abs((float)y - s.y / 2) / (s.y / 2);
        float shake = std::sin(t * frequency + y * 0.05f) * amplitude * edgeFactor;
        for (unsigned x = 0; x < s.x; ++x) {
            int sampleX = static_cast<int>(std::round(x + shake));
            unsigned sx = clampu(sampleX, s.x);
            sf::Color c = src.getPixel(sx, y);
            dst.setPixel(x, y, c);
        }
    }
}

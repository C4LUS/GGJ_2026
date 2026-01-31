#include "BlurEffect.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>

void BlurEffect::apply(const sf::Image& src, sf::Image& dst, float /*time*/) {
    sf::Vector2u s = src.getSize();
    dst.create(s.x, s.y, sf::Color::Transparent);

    int radius = std::max(1, static_cast<int>(std::round(intensity)));
    int w = s.x, h = s.y;

    // First pass: horizontal blur
    std::vector<sf::Color> horiz(w * h);
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            int r = 0, g = 0, b = 0, a = 0, count = 0;
            for (int dx = -radius; dx <= radius; ++dx) {
                int nx = x + dx;
                if (nx < 0 || nx >= w) continue;
                sf::Color c = src.getPixel(nx, y);
                r += c.r; g += c.g; b += c.b; a += c.a;
                ++count;
            }
            horiz[y * w + x] = count > 0 ? sf::Color(r / count, g / count, b / count, a / count) : src.getPixel(x, y);
        }
    }

    // Second pass: vertical blur
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            int r = 0, g = 0, b = 0, a = 0, count = 0;
            for (int dy = -radius; dy <= radius; ++dy) {
                int ny = y + dy;
                if (ny < 0 || ny >= h) continue;
                sf::Color c = horiz[ny * w + x];
                r += c.r; g += c.g; b += c.b; a += c.a;
                ++count;
            }
            if (count > 0)
                dst.setPixel(x, y, sf::Color(r / count, g / count, b / count, a / count));
            else
                dst.setPixel(x, y, src.getPixel(x, y));
        }
    }
}

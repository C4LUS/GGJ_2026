#include "GrayscaleEffect.hpp"

void GrayscaleEffect::apply(const sf::Image& src, sf::Image& dst, float /*time*/) {
    sf::Vector2u s = src.getSize();
    dst.create(s.x, s.y, sf::Color::Transparent);

    for (unsigned y = 0; y < s.y; ++y) {
        for (unsigned x = 0; x < s.x; ++x) {
            sf::Color c = src.getPixel(x, y);
            sf::Uint8 avg = static_cast<sf::Uint8>((c.r + c.g + c.b) / 3);
            dst.setPixel(x, y, sf::Color(avg, avg, avg, c.a));
        }
    }
}

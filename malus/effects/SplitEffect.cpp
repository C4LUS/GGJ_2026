#include "SplitEffect.hpp"
#include <SFML/Graphics.hpp>

void SplitEffect::apply(const sf::Image& src, sf::Image& out, float /*t*/) {
    sf::Vector2u size = src.getSize();
    out.create(size.x, size.y, sf::Color::Transparent);
    unsigned mid = size.x / 2;
    // Copy right half to left, left half to right
    for (unsigned y = 0; y < size.y; ++y) {
        for (unsigned x = 0; x < mid; ++x) {
            out.setPixel(x + mid, y, src.getPixel(x, y));
        }
        for (unsigned x = mid; x < size.x; ++x) {
            out.setPixel(x - mid, y, src.getPixel(x, y));
        }
    }
}

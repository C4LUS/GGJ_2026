#include "ReverseEffect.hpp"
#include <SFML/Graphics.hpp>

void ReverseEffect::apply(const sf::Image& src, sf::Image& out, float /*t*/) {
    sf::Vector2u size = src.getSize();
    out.create(size.x, size.y, sf::Color::Transparent);
    for (unsigned y = 0; y < size.y; ++y) {
        for (unsigned x = 0; x < size.x; ++x) {
            out.setPixel(x, size.y - 1 - y, src.getPixel(x, y));
        }
    }
}

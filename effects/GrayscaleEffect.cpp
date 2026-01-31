#include "GrayscaleEffect.hpp"

void GrayscaleEffect::apply(const sf::Image& src, sf::Image& dst, float /*time*/) {
    sf::Vector2u s = src.getSize();
    dst.create(s.x, s.y, sf::Color::Transparent);

    for (unsigned y = 0; y < s.y; ++y) {
        for (unsigned x = 0; x < s.x; ++x) {
            sf::Color c = src.getPixel(x, y);
            unsigned char gray = static_cast<unsigned char>(
                (0.299f * c.r + 0.587f * c.g + 0.114f * c.b)
            );
            // Lerp between original and gray by intensity
            sf::Uint8 r = static_cast<sf::Uint8>(c.r * (1 - intensity) + gray * intensity);
            sf::Uint8 g = static_cast<sf::Uint8>(c.g * (1 - intensity) + gray * intensity);
            sf::Uint8 b = static_cast<sf::Uint8>(c.b * (1 - intensity) + gray * intensity);
            dst.setPixel(x, y, sf::Color(r, g, b, c.a));
        }
    }
}

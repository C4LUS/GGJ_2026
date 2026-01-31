#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>
#include <iostream>
#include "FrameEffect.hpp"
#include "GrayscaleEffect.hpp"
#include "WaveDistortionEffect.hpp"

int main() {
    sf::RenderWindow window({800, 600}, "Frame Effects Example");
    window.setFramerateLimit(60);

    // Simple scene to render: moving circle and rectangle
    sf::CircleShape circle(60.f);
    circle.setFillColor(sf::Color::Cyan);
    circle.setPosition(100, 200);

    sf::RectangleShape rect({200, 150});
    rect.setFillColor(sf::Color(255, 128, 64));
    rect.setPosition(400, 250);

    sf::RenderTexture renderTex;
    renderTex.create(800, 600);

    // Setup effects (persistent, named) and add once to chain
    EffectChain chain;
    auto gptr = std::make_unique<GrayscaleEffect>(20.0f, "grayscale");
    auto wptr = std::make_unique<WaveDistortionEffect>(8.f, 0.06f, 2.f, "wave");
    // start disabled/enabled according to desired defaults
    gptr->setEnabled(false);
    wptr->setEnabled(true);
    chain.addEffect(std::move(gptr));
    chain.addEffect(std::move(wptr));

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) window.close();
            if (ev.type == sf::Event::KeyPressed) {
                if (ev.key.code == sf::Keyboard::G) {
                    std::cout << "Grayscale On/Off" << std::endl;
                    chain.toggle("grayscale");
                }
                if (ev.key.code == sf::Keyboard::W) {
                    std::cout << "Wave On/Off" << std::endl;
                    chain.toggle("wave");
                }
                if (ev.key.code == sf::Keyboard::I) {
                    // Increase grayscale intensity
                    auto *fe = chain.getEffect("grayscale");
                    if (fe) {
                        auto *g = dynamic_cast<GrayscaleEffect*>(fe);
                        if (g) { g->increaseIntensity(0.1f); std::cout << "Grayscale intensity: " << g->getIntensity() << std::endl; }
                    }
                }
                if (ev.key.code == sf::Keyboard::K) {
                    // Decrease grayscale intensity
                    auto *fe = chain.getEffect("grayscale");
                    if (fe) {
                        auto *g = dynamic_cast<GrayscaleEffect*>(fe);
                        if (g) { g->decreaseIntensity(0.1f); std::cout << "Grayscale intensity: " << g->getIntensity() << std::endl; }
                    }
                }
            }
        }

        float t = clock.getElapsedTime().asSeconds();

        // animate
        circle.setPosition(120 + std::sin(t) * 80.f, 200 + std::cos(t * 0.8f) * 20.f);

        // Render scene to texture
        renderTex.clear(sf::Color::Black);
        renderTex.draw(circle);
        renderTex.draw(rect);
        renderTex.display();

        // Capture as image
        sf::Image frame = renderTex.getTexture().copyToImage();
        sf::Image out;

        // Apply the configured chain (effects were added once and can be toggled)
        chain.apply(frame, out, t);

        // Upload to texture and draw
        sf::Texture resultTex;
        resultTex.loadFromImage(out);
        sf::Sprite sprite(resultTex);

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}

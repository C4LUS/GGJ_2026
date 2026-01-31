
#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>
#include <iostream>
#include "effects/FrameEffect.hpp"
#include "effects/GrayscaleEffect.hpp"
#include "effects/WaveDistortionEffect.hpp"
#include "effects/ScreenShakeEffect.hpp"
#include "effects/BlurEffect.hpp"
#include "Malus.hpp"

int main() {
    // Load background
    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("effects/voiture.png")) {
        std::cerr << "Failed to load voiture.png" << std::endl;
        return 1;
    }
    sf::Sprite bgSprite(bgTexture);
    sf::Vector2u texSize = bgTexture.getSize();
    bgSprite.setScale(800.f / texSize.x, 600.f / texSize.y);

    sf::RenderWindow window({800, 600}, "Malus Effects Example");
    window.setFramerateLimit(60);

    sf::CircleShape circle(60.f);
    circle.setFillColor(sf::Color::Cyan);
    circle.setPosition(100, 200);

    sf::RectangleShape rect({200, 150});
    rect.setFillColor(sf::Color(255, 128, 64));
    rect.setPosition(400, 250);

    sf::RenderTexture renderTex;
    renderTex.create(800, 600);

    EffectChain chain;
    auto gptr = std::make_unique<GrayscaleEffect>(20.0f, "grayscale");
    auto wptr = std::make_unique<WaveDistortionEffect>(8.f, 0.06f, 2.f, "wave");
    auto sptr = std::make_unique<ScreenShakeEffect>(24.f, 8.f, 2.f, "shake");
    auto bptr = std::make_unique<BlurEffect>(4.0f, "blur");
    gptr->setEnabled(false);
    wptr->setEnabled(false);
    sptr->setEnabled(false);
    bptr->setEnabled(false);
    chain.addEffect(std::move(gptr));
    chain.addEffect(std::move(wptr));
    chain.addEffect(std::move(sptr));
    chain.addEffect(std::move(bptr));

    Malus malus;
    malus.setHandler(Malus::Alcohol, [&chain]() { chain.setEnabled("blur", true); });
    malus.setHandler(Malus::Noise, [&chain]() { chain.setEnabled("grayscale", true); });
    malus.setHandler(Malus::Smell, [&chain]() { chain.setEnabled("wave", true); });
    malus.setHandler(Malus::Shake, [&chain]() { chain.setEnabled("shake", true); });

    malus.add(Malus::Alcohol, 2);
    malus.add(Malus::Noise, 3);
    malus.add(Malus::Smell, 1);
    malus.add(Malus::Shake, 4);

    sf::Clock clock;
    bool malusTriggered = false;

    while (window.isOpen()) {
        sf::Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) window.close();
            if (ev.type == sf::Event::KeyPressed) {
                if (ev.key.code == sf::Keyboard::Space && !malusTriggered) {
                    malus.run();
                    malusTriggered = true;
                }
                if (ev.key.code == sf::Keyboard::R) {
                    chain.setEnabled("blur", false);
                    chain.setEnabled("grayscale", false);
                    chain.setEnabled("wave", false);
                    chain.setEnabled("shake", false);
                    malusTriggered = false;
                }
            }
        }

        float t = clock.getElapsedTime().asSeconds();
        circle.setPosition(120 + std::sin(t) * 80.f, 200 + std::cos(t * 0.8f) * 20.f);

        renderTex.clear(sf::Color::Black);
        renderTex.draw(bgSprite);
        renderTex.draw(circle);
        renderTex.draw(rect);
        renderTex.display();

        sf::Image frame = renderTex.getTexture().copyToImage();
        sf::Image out;
        chain.apply(frame, out, t);

        sf::Texture resultTex;
        resultTex.loadFromImage(out);
        sf::Sprite sprite(resultTex);

        window.clear();
        window.draw(sprite);
        window.display();
    }
    return 0;
}

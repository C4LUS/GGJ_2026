#include "../include/Character.hpp"
#include <iostream>

Character::Character(Assets& assets, GameID::Texture texID, 
                     int frameW, int frameH, int startX, int startY, int frames)
    : m_timer(0), m_currentFrame(0), m_animDirection(1)
{
    // C'EST ICI QUE TU UTILISES TON NOUVEAU GET(ENUM)
    m_sprite.setTexture(assets.get(texID));

    // Config animation par defaut
    addAnimation("default", startX, startY, frameW, frameH, frames, 0.15f);
    setAnimation("default");
}

void Character::addAnimation(std::string name, int x, int y, int w, int h, int frames, float speed) {
    m_animations[name] = {x, y, w, h, frames, speed};
}

void Character::setAnimation(std::string name) {
    if (m_animations.find(name) == m_animations.end() || m_currentAnim == name) return;

    m_currentAnim = name;
    m_currentFrame = 0;
    m_timer = 0;
    applyAnimData(m_animations[name]);
}

void Character::update(float dt) {
    if (m_currentAnim.empty()) return;
    AnimData& d = m_animations[m_currentAnim];

    m_timer += dt;
    if (m_timer >= d.speed) {
        m_timer = 0;
        m_currentFrame += m_animDirection;

        // Ping-pong loop
        if (m_currentFrame >= d.numFrames - 1) {
            m_currentFrame = d.numFrames - 1;
            m_animDirection = -1;
        } else if (m_currentFrame <= 0) {
            m_currentFrame = 0;
            m_animDirection = 1;
        }
        applyAnimData(d);
    }
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_sprite, states);
}

void Character::applyAnimData(const AnimData& d) {
    int left = d.start_x + (m_currentFrame * d.width);
    m_sprite.setTextureRect(sf::IntRect(left, d.start_y, d.width, d.height));
}
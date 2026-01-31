#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/Graphics.hpp>
#include "Assets.hpp"
#include "GameId.hpp"

// Structure simple pour les données d'anim (peut rester dans le .hpp ou bouger)
struct AnimData {
    int start_x, start_y;
    int width, height;
    int numFrames;
    float speed;
};

class Character : public sf::Drawable, public sf::Transformable {
public:
    // Constructeur prend maintenant GameID::Texture
    Character(Assets& assets, GameID::Texture texID, 
              int frameW, int frameH, int startX, int startY, int frames);

    void addAnimation(std::string name, int x, int y, int w, int h, int frames, float speed);
    void setAnimation(std::string name);
    void update(float dt);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void applyAnimData(const AnimData& d);

    sf::Sprite m_sprite;
    std::string m_currentAnim;
    std::map<std::string, AnimData> m_animations;
    
    float m_timer;
    int m_currentFrame;
    int m_animDirection;
};

#endif
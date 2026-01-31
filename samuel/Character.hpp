#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "Assets.hpp" // On inclut ta classe Assets

struct AnimData {
    int start_x, start_y; // Coin haut-gauche de la première frame
    int width, height;    // Taille d'une frame
    int numFrames;        // Combien d'images
    float speed;          // Vitesse
};

// On hérite de Drawable (pour window.draw(perso)) 
// et Transformable (pour setPosition, setScale, setRotation...)
class Character : public sf::Drawable, public sf::Transformable {
public:
    // CONSTRUCTEUR MODIFIÉ
    // On passe 'Assets&' (référence) et le nom de la texture
    Character(Assets& assets, std::string textureName, int frameWidth, int frameHeight, int start_x, int start_y, int numFrames)
        : name(textureName)
    {
        // 1. On récupère la texture depuis ton Assets
        // Attention : la texture ne doit pas être détruite tant que le perso existe !
        sprite.setTexture(assets.getTexture(textureName));

        // 2. On configure l'animation par défaut
        // (J'utilise tes paramètres pour créer l'anim "default")
        addAnimation("default", start_x, start_y, frameWidth, frameHeight, numFrames, 0.15f);
        
        // 3. On lance l'animation
        setAnimation("default");
    }

    // Plus besoin de réécrire setScale ou setPosition !
    // sf::Transformable le fait pour toi.

    // Ajoute une nouvelle animation à la liste
    void addAnimation(std::string animName, int x, int y, int w, int h, int frames, float speed) {
        animations[animName] = {x, y, w, h, frames, speed};
    }

    // Change l'animation en cours
    void setAnimation(std::string animName) {
        // Si l'anim n'existe pas ou qu'on la joue déjà, on ne fait rien
        if (animations.find(animName) == animations.end() || currentAnimName == animName) {
            return;
        }

        currentAnimName = animName;
        currentFrame = 0;
        animDirection = 1;
        timer = 0;
        
        // On applique tout de suite le premier rectangle pour ne pas attendre 1 frame
        applyAnimData(animations[animName]);
    }

    // À appeler dans ta boucle de jeu (update)
    void updateAnimation(float deltaTime) {
        if (currentAnimName.empty()) return;

        AnimData& d = animations[currentAnimName]; 

        timer += deltaTime;
        
        // Est-il temps de changer d'image ?
        if (timer >= d.speed) {
            timer = 0;
            currentFrame += animDirection;

            // --- Ta logique Ping-Pong (Aller-Retour) ---
            // Si on dépasse la fin
            if (currentFrame >= d.numFrames - 1) {
                currentFrame = d.numFrames - 1; // On cale sur la dernière
                animDirection = -1;             // On recule
            } 
            // Si on dépasse le début
            else if (currentFrame <= 0) {
                currentFrame = 0;
                animDirection = 1;              // On avance
            }

            // Mise à jour du rectangle de texture
            updateTextureRect(d);
        }
    }

private:
    // C'est cette fonction spéciale qui permet de faire window.draw(character)
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        // On applique les transformations (position/scale/rotation du Character) au sprite
        states.transform *= getTransform();
        target.draw(sprite, states);
    }

    // Helper pour appliquer le découpage
    void applyAnimData(const AnimData& d) {
        updateTextureRect(d);
    }

    // Calcul mathématique pour trouver le bon rectangle sur la spritesheet
    void updateTextureRect(const AnimData& d) {
        // Calcul : x de départ + (numéro image * largeur image)
        int rectLeft = d.start_x + (currentFrame * d.width);
        int rectTop = d.start_y;

        sprite.setTextureRect(sf::IntRect(rectLeft, rectTop, d.width, d.height));
    }

private:
    sf::Sprite sprite;
    std::string name;
    std::string currentAnimName;

    std::map<std::string, AnimData> animations;

    float timer = 0.f;
    int currentFrame = 0;
    int animDirection = 1;
};

#endif
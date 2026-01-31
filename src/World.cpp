#include "../include/World.hpp"
#include <iostream>

// Destructeur obligatoire car on utilise des unique_ptr dans le .hpp
World::~World() = default;

World::World(Context context)
    : mContext(context)
    , mWindow(*context.window)
{
    // 1. Création du personnage (Le PlayerCar = Homme_pauvre_final.png)
    // On utilise ton constructeur : assets, enum, frameW, frameH, startX, startY, frames
    mPlayer = std::make_unique<Character>(
        *mContext.assets, 
        GameID::Texture::PlayerCar, 
        90, 200, // Taille d'une frame (à ajuster selon ton PNG)
        0, 0,    // On commence en haut à gauche
        4        // 1 seule frame pour commencer
    );

    // 2. Positionnement simple au centre de l'écran
    mPlayer->setPosition(mWindow.getSize().x / 2.f, mWindow.getSize().y / 2.f);
    
    std::cout << "[World] Character cree et positionne." << std::endl;
}

void World::update(sf::Time dt) {
    float dtSec = dt.asSeconds();
    float speed = 400.f; 
    sf::Vector2f movement(0.f, 0.f);

    // --- HORIZONTAL ---
    if (mContext.input->isActionActive(GameID::Action::SteerLeft)) {
        movement.x -= speed;
    }
    if (mContext.input->isActionActive(GameID::Action::SteerRight)) {
        movement.x += speed;
    }

    // --- VERTICAL ---
    if (mContext.input->isActionActive(GameID::Action::MoveUp)) {
        movement.y -= speed;
    }
    if (mContext.input->isActionActive(GameID::Action::MoveDown)) {
        movement.y += speed;
    }

    // On applique le mouvement final
    mPlayer->move(movement * dtSec);

    // On n'oublie pas de mettre à jour l'animation (le timer de Character)
    mPlayer->update(dtSec);
}
void World::draw() {
    // On dessine le personnage
    // Rappel : mPlayer est un unique_ptr, donc on le déréférence avec *
    mWindow.draw(*mPlayer);
}

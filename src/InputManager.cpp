#include "../include/InputManager.hpp"

// Constructeur vide
InputManager::InputManager() {
    // Rien à faire pour l'instant
}

// Fonction vide
void InputManager::bindKey(sf::Keyboard::Key, GameID::Action) {
    // On ne fait rien
}

// Retourne toujours false (comme ça, aucune action n'est détectée)
bool InputManager::isActionActive(GameID::Action) const {
    return false;
}

// Retourne toujours false
bool InputManager::isActionTriggered(GameID::Action, const sf::Event &) const {
    return false;
}
#include "InsideCar.hpp"
 
PhoneSystem::PhoneSystem(const TextureHolder& texture) {
    std::cout << "Phone texture" << std::endl;
};

void PhoneSystem::update(sf::Time dt) {
    
};

bool PhoneSystem::handleEvent(const sf::Event &event, const sf::RenderWindow &window) {
    if (mState != Ringing)
        return false;
    if (event.type == sf::Event::MouseButtonPressed) {
        mState = Talking;
        return true;
    }

    return false;
};

GameID::Mask PhoneSystem::getRequiredMask() const {
   return requiredMak;
};

//MASK

MaskSelector::MaskSelector(Context context) {
};

void MaskSelector::handleEvent(const sf::Event &event) {

};

GameID::Mask MaskSelector::getSelectedMask() const {
    
};
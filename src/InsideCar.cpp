#include "../include/InsideCar.hpp"
#include <cstdlib> 
#include <cmath>
#include <algorithm>

// --- PHONE SYSTEM ---

PhoneSystem::PhoneSystem(Context context) {
    mState = Idle;
    time = sf::Time::Zero;
    mRequiredMask = GameID::Malus::None;

    // Note: Remplace GameID::Texture::PlayerCar par Phone quand tu l'auras
    mPhoneCharacter = std::make_unique<Character>(
        *context.assets, GameID::Texture::PlayerCar,
        100, 100, 0, 0, 1
    );

    mPhoneCharacter->setPosition(600.f, 400.f);
    mSubtitleText.setFont(context.assets->get(GameID::Font::Main));
    mSubtitleText.setCharacterSize(24);
    mSubtitleText.setFillColor(sf::Color::White);
    mSubtitleText.setPosition(50.f, 550.f);
}

void PhoneSystem::update(sf::Time dt) {
    time += dt;
    mPhoneCharacter->update(dt.asSeconds());

    switch (mState) {
        case Idle:
            if (time > sf::seconds(2.f)) {
                mState = Ringing;
                time = sf::Time::Zero;
                mSubtitleText.setString("Incoming call! (Click the Red Box)");
            }
            break;
        case Ringing:
            if (time > sf::seconds(5.f)) {
                mState = Finished;
                time = sf::Time::Zero;
                mSubtitleText.setString("Missed call.");
            }
            break;
        case Talking:
            if (mRequiredMask == GameID::Malus::None) {
                int randVal = std::rand() % 5;
                if (randVal == 0) mRequiredMask = GameID::Malus::Alcool;
                else if (randVal == 1) mRequiredMask = GameID::Malus::Stinky;
                else if (randVal == 2) mRequiredMask = GameID::Malus::Headset;
                else if (randVal == 3) mRequiredMask = GameID::Malus::Coke; // Si Coke existe
                else mRequiredMask = GameID::Malus::Fat;

                mSubtitleText.setString("Voice: 'I need a driver...' (Check clues!)");
            }
            if (time > sf::seconds(3.f)) {
                mState = Finished;
                time = sf::Time::Zero;
                mSubtitleText.setString("Call finished. Select a Mask!");
            }
            break;
        case Finished: break;
    }
}

bool PhoneSystem::handleEvent(const sf::Event &event, const sf::RenderWindow &window) {
    (void)window;
    if (mState == Ringing) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
            
            // On utilise les bounds réelles pour cliquer sur le téléphone
            if (mPhoneCharacter->getGlobalBounds().contains(mousePos)) {
                std::cout << "Input: Phone Clicked!" << std::endl;
                mState = Talking;
                time = sf::Time::Zero;
                return true;
            }
        }
    }
    return false;
}

void PhoneSystem::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (mState == Ringing) {
        float scale = 1.0f + std::sin(time.asSeconds() * 10.f) * 0.1f;
        mPhoneCharacter->setScale(scale, scale);
    }
    target.draw(*mPhoneCharacter, states);
    target.draw(mSubtitleText, states);
}

GameID::Malus PhoneSystem::getRequiredMask() const { return mRequiredMask; }
bool PhoneSystem::isWaitingForMask() const { return mState == Finished && mRequiredMask != GameID::Malus::None; }
bool PhoneSystem::isCallFinished() const { return mState == Finished; }
void PhoneSystem::reset() { mState = Idle; time = sf::Time::Zero; mRequiredMask = GameID::Malus::None; mSubtitleText.setString(""); }

// --- MASK SELECTOR ---

MaskSelector::MaskSelector(Context context) {
    mButtons.clear();

    std::map<GameID::Malus, GameID::Texture> maskMap = {
        {GameID::Malus::Alcool,  GameID::Texture::Mask_Alcool},
        {GameID::Malus::Stinky,  GameID::Texture::Mask_Stinky},
        {GameID::Malus::Headset, GameID::Texture::Mask_Headset},
        {GameID::Malus::Fat,     GameID::Texture::Mask_Fat}
    };

    float startX = 100.f;
    float startY = 100.f; // Remis plus haut pour voir les 4 boutons
    float offsetY = 120.f; 

    for (auto const& [malusID, textureID] : maskMap) {
        Button btn;
        btn.maskID = malusID;
        btn.isSelected = false;

        sf::Texture& tex = context.assets->get(textureID);
        sf::Vector2u size = tex.getSize();

        btn.icon = std::make_unique<Character>(
            *context.assets, textureID, 
            size.x, size.y, 
            0, 0, 1
        );

        // Correction du Scale : On veut que l'image fasse environ 100 pixels
        float maxSide = std::max((float)size.x, (float)size.y);
        float factor = 100.f / maxSide;
        
        btn.baseScale = factor;
        btn.icon->setScale(factor, factor);
        btn.icon->setPosition(startX, startY);

        mButtons.push_back(std::move(btn));
        startY += offsetY;
    }
}

void MaskSelector::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (const auto &button : mButtons) {
        if (button.isSelected) {
            // On multiplie le scale de base par 1.2
            float s = button.baseScale * 1.2f;
            button.icon->setScale(s, s);
        } else {
            // On revient au scale de base (et pas à 1.0 !)
            button.icon->setScale(button.baseScale, button.baseScale);
        }
        target.draw(*button.icon, states);
    }
}

void MaskSelector::handleEvent(const sf::Event &event) {
    if (event.type != sf::Event::MouseButtonPressed || event.mouseButton.button != sf::Mouse::Left)
        return;

    sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));

    for (auto &button : mButtons) {
        // MAGIE : getGlobalBounds calcule automatiquement la zone de collision
        // en fonction du scale et de la position du Character.
        if (button.icon->getGlobalBounds().contains(mousePos)) {
            // Déselectionner les autres
            for (auto &b : mButtons) b.isSelected = false;

            button.isSelected = true;
            std::cout << "Mask Selected: " << static_cast<int>(button.maskID) << std::endl;
            break;
        }
    }
}

GameID::Malus MaskSelector::getSelectedMask() const {
    for (const auto &button : mButtons) {
        if (button.isSelected) return button.maskID;
    }
    return GameID::Malus::None;
}

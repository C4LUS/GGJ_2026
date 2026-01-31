#include "include/InsideCar.hpp"
 
PhoneSystem::PhoneSystem(const TextureHolder& texture) {
    
   // Rectangle pour représenter le téléphone
    mState = Idle;
    time = sf::Time::Zero;
    mSprite.setPosition(600.f, 400.f);
    mSprite.setColor(sf::Color::Red); // téléphone rouge pour visibilité
    mSprite.setTextureRect(sf::IntRect(0, 0, 100, 100));

    // Texte pour sous-titres
    mSubtitleText.setCharacterSize(24);
    mSubtitleText.setFillColor(sf::Color::White);
    mSubtitleText.setPosition(50.f, 550.f);
};

void PhoneSystem::update(sf::Time dt) {
    time += dt;

    switch (mState) {
        case Idle:
            if (time > sf::seconds(5.f)) {
                mState = Ringing;
                time = sf::Time::Zero;
                mSubtitleText.setString("Incoming call!!!!!!!!!");
                std::cout << "Incoming call!!!!" << std::endl;
            }
            break;
        case Ringing:
            if (time > sf::seconds(5.f)) {
                mState = Finished;
                time = sf::Time::Zero;
                mSubtitleText.setString("Missed call.");
                std::cout << "Missed call" << std::endl;
            }
            break;
        case Talking:
            std::cout << "talkiiiiiing" << std::endl; 
        
            std::cout << "talking" << std::endl;
            // int randMalus = rand() % 5;
            switch(rand() % 5) {
                case 0: mRequiredMask = GameID::Malus::Alcool; break;
                case 1: mRequiredMask = GameID::Malus::Stinky; break;
                case 2: mRequiredMask = GameID::Malus::Headset; break;
                case 3: mRequiredMask = GameID::Malus::Coke; break;
                case 4: mRequiredMask = GameID::Malus::Fat; break;
            }
            mSubtitleText.setString("Choose the correct protection!!");
            std::cout << "choose the correct protection" << std::endl;

            if (time > sf::seconds(3.f)) {
                mState = Finished;
                time = sf::Time::Zero;
                mSubtitleText.setString("Call finished.");
                std::cout << "call finished" << std::endl;
            }
            break;
        case Finished:
            if (time > sf::seconds(2.f)) {
                mState = Idle;
                time = sf::Time::Zero;
                mSubtitleText.setString("");
                mRequiredMask = GameID::Malus::None;
            }
            break;
    };
};

bool PhoneSystem::handleEvent(const sf::Event &event, const sf::RenderWindow &window) {
    if (mState == Ringing) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x),
                                  static_cast<float>(event.mouseButton.y));

            if (mSprite.getGlobalBounds().contains(mousePos)) {
                std::cout << "click on phone" << std::endl;
                mState = Talking;
                time = sf::Time::Zero;
                return true; // appel décroché
            }
        }
    }

    return false;
};

GameID::Malus PhoneSystem::getRequiredMask() const {
    return mRequiredMask;
};

void PhoneSystem::draw(sf::RenderTarget& target,
                       sf::RenderStates states) const
{
    sf::RectangleShape rect(
        sf::Vector2f(mSprite.getGlobalBounds().width,
                     mSprite.getGlobalBounds().height)
    );
    rect.setPosition(mSprite.getPosition());
    rect.setFillColor(mSprite.getColor());

    target.draw(rect, states);
    target.draw(mSubtitleText, states);
}

bool PhoneSystem::isWaitingForMask() const {
    return mState == Finished && mRequiredMask != GameID::Malus::None;
}

bool PhoneSystem::isCallFinished() const {
    return mState == Finished;
}

void PhoneSystem::reset() {
    mState = Idle;
    time = sf::Time::Zero;
    mRequiredMask = GameID::Malus::None;
}

//MASK

MaskSelector::MaskSelector(Context context) {
    mButtons.clear();

    float y = 100.f;       // position de départ
    float offsetY = 70.f;  // écart vertical entre boutons
    float width = 150.f;
    float height = 50.f;

    // Liste des malus
    for (auto malus : {GameID::Malus::Alcool, GameID::Malus::Stinky,
                       GameID::Malus::Headset, GameID::Malus::Coke,
                       GameID::Malus::Fat}) {

        Button btn;
        btn.isSelected = false;
        btn.maskID = malus;

        // Crée un rectangle coloré pour représenter le bouton
        btn.sprite.setPosition(100.f, y);
        btn.sprite.setTextureRect(sf::IntRect(0, 0, static_cast<int>(width), static_cast<int>(height)));

        // On utilise setColor pour chaque malus (test visuel)
        switch (malus) {
            case GameID::Malus::Alcool:   btn.sprite.setColor(sf::Color::Red); break;
            case GameID::Malus::Stinky:   btn.sprite.setColor(sf::Color::Green); break;
            case GameID::Malus::Headset:  btn.sprite.setColor(sf::Color::Blue); break;
            case GameID::Malus::Coke:     btn.sprite.setColor(sf::Color::Cyan); break;
            case GameID::Malus::Fat:      btn.sprite.setColor(sf::Color::Magenta); break;
            default: btn.sprite.setColor(sf::Color::White); break;
        }

        // On crée un rectangle shape pour le rendu (sprite reste vide)
        sf::RectangleShape rect(sf::Vector2f(width, height));
        rect.setPosition(100.f, y);
        rect.setFillColor(btn.sprite.getColor());

        // On stocke dans le sprite via setTextureRect et couleur (pratique SFML)
        btn.sprite.setTextureRect(sf::IntRect(0,0,static_cast<int>(width), static_cast<int>(height)));
        btn.sprite.setColor(rect.getFillColor());

        mButtons.push_back(btn);
        y += offsetY;
    }
}

void MaskSelector::handleEvent(const sf::Event &event) {
    if (event.type != sf::Event::MouseButtonPressed || event.mouseButton.button != sf::Mouse::Left)
        return;

    sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x),
                          static_cast<float>(event.mouseButton.y));

    for (auto &button : mButtons) {
        if (button.sprite.getGlobalBounds().contains(mousePos)) {
            for (auto &b : mButtons) b.isSelected = false;
            button.isSelected = true;
            break;
        }
    }
}

GameID::Malus MaskSelector::getSelectedMask() const {
    for (const auto &button : mButtons) {
        if (button.isSelected)
            return button.maskID;
    }
    return GameID::Malus::None;
}

void MaskSelector::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (const auto &button : mButtons) {
        // Dessine le rectangle coloré
        sf::RectangleShape rect(sf::Vector2f(button.sprite.getGlobalBounds().width,
                                             button.sprite.getGlobalBounds().height));
        rect.setPosition(button.sprite.getPosition());
        rect.setFillColor(button.sprite.getColor());

        // Si sélectionné, ajout d’un contour jaune
        if (button.isSelected) {
            rect.setOutlineThickness(3.f);
            rect.setOutlineColor(sf::Color::Yellow);
        }

        target.draw(rect, states);
    }
}
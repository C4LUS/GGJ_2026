#include "../include/InsideCarState.hpp"
#include "../include/GameId.hpp"
#include <iostream>

InsideCarState::InsideCarState(StateStack &stack, Context context)
    : State(stack, context)
    , mPhoneSystem(context)
    , mMaskSelector(context) 
{
    std::cout << "[Stack] Entered INSIDE CAR State" << std::endl;

    sf::RenderWindow &window = *getContext().window;

    // --- AFFICHAGE DU BACKGROUND ---
    // On utilise ton Enum GameID::Texture::Background pour choper Ville.png
    sf::Texture& bgTex = context.assets->get(GameID::Texture::Background);
    
    // On l'applique au Sprite (mBackground doit être un sf::Sprite maintenant)
    mBackgroundSprite.setTexture(bgTex);

    // OPTIONNEL : Redimensionner l'image pour qu'elle fasse pile la taille de la fenêtre
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u texSize = bgTex.getSize();
    mBackgroundSprite.setScale(
        (float)windowSize.x / texSize.x, 
        (float)windowSize.y / texSize.y
    );

    // Setup du texte (garde ton code actuel)
    mInfoText.setFont(context.assets->get(GameID::Font::Main));
    mInfoText.setString("1. Wait for Call  2. Select Mask  3. Press ENTER to Drive");
    mInfoText.setCharacterSize(20);
    mInfoText.setPosition(10, 10);
}

void InsideCarState::draw() {
    sf::RenderWindow &window = *getContext().window;
    
    // On dessine la ville en fond
    window.draw(mBackgroundSprite);
    
    window.draw(mInfoText);
    window.draw(mPhoneSystem);
    window.draw(mMaskSelector);
}


bool InsideCarState::update(sf::Time dt) {
  mPhoneSystem.update(dt);
  return true;
}

bool InsideCarState::handleEvent(const sf::Event &event) {
  // 1. Pass input to Systems
  mPhoneSystem.handleEvent(event, *getContext().window);
  mMaskSelector.handleEvent(event);

  // 2. Logic: Start Engine (Enter Key)
  if (event.type == sf::Event::KeyPressed &&
      event.key.code == sf::Keyboard::Enter) {

    // Only allow start if call is finished (optional rule)
    if (mPhoneSystem.isCallFinished()) {

      // --- CRITICAL: SAVE DATA TO SESSION ---
      SessionData *session = getContext().session;

      session->currentMask = mMaskSelector.getSelectedMask();
      session->requiredMaskForNextRun = mPhoneSystem.getRequiredMask();

      std::cout << "[Session] Saved Data -> Mask: "
                << static_cast<int>(session->currentMask) << " | Threat: "
                << static_cast<int>(session->requiredMaskForNextRun)
                << std::endl;

      // Switch to Driving
      requestStackPop();
      requestStackPush(
          GameID::State::Driving); // Ensure Driving state is registered!
    } else {
      std::cout << "[Game] Finish the call first!" << std::endl;
    }
  }

  return false;
}

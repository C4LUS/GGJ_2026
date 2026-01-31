#include "../include/InsideCar.hpp"
#include <cstdlib> // For rand()

// --- PHONE SYSTEM ---

PhoneSystem::PhoneSystem(Context context) {
  mState = Idle;
  time = sf::Time::Zero;
  mRequiredMask = GameID::Malus::None;

  // Use the Assets manager from Context
  // Ensure "Phone" is a valid Texture enum or use a placeholder
  // mSprite.setTexture(context.assets->get(GameID::Texture::Phone));

  // For now, using a placeholder Red Rectangle via Sprite color since we might
  // not have the texture loaded
  mSprite.setPosition(600.f, 400.f);
  mSprite.setColor(sf::Color::Red);
  // Set a default size for the sprite logic (clickable area)
  mSprite.setTextureRect(sf::IntRect(0, 0, 100, 100));

  // Setup Text using the Assets manager
  // Note: We access the font via the new Assets system
  mSubtitleText.setFont(context.assets->get(GameID::Font::Main));
  mSubtitleText.setCharacterSize(24);
  mSubtitleText.setFillColor(sf::Color::White);
  mSubtitleText.setPosition(50.f, 550.f);
}

void PhoneSystem::update(sf::Time dt) {
  time += dt;

  switch (mState) {
  case Idle:
    if (time > sf::seconds(2.f)) { // Shortened for debugging
      mState = Ringing;
      time = sf::Time::Zero;
      mSubtitleText.setString("Incoming call! (Click the Red Box)");
      std::cout << "State: Ringing" << std::endl;
    }
    break;
  case Ringing:
    if (time > sf::seconds(5.f)) {
      mState = Finished;
      time = sf::Time::Zero;
      mSubtitleText.setString("Missed call.");
      std::cout << "State: Missed" << std::endl;
    }
    break;
  case Talking:
    // Just picked up
    if (mRequiredMask == GameID::Malus::None) {
      // Randomize threat
      int randVal = std::rand() % 5;
      switch (randVal) {
      case 0:
        mRequiredMask = GameID::Malus::Alcool;
        break;
      case 1:
        mRequiredMask = GameID::Malus::Stinky;
        break;
      case 2:
        mRequiredMask = GameID::Malus::Headset;
        break;
      case 3:
        mRequiredMask = GameID::Malus::Coke;
        break;
      case 4:
        mRequiredMask = GameID::Malus::Fat;
        break;
      }
      mSubtitleText.setString("Voice: 'I need a driver...' (Check clues!)");
      std::cout << "State: Talking (Threat Generated: "
                << static_cast<int>(mRequiredMask) << ")" << std::endl;
    }

    if (time > sf::seconds(3.f)) {
      mState = Finished;
      time = sf::Time::Zero;
      mSubtitleText.setString("Call finished. Select a Mask!");
      std::cout << "State: Finished" << std::endl;
    }
    break;
  case Finished:
    // Waiting for player to select mask and start engine
    break;
  };
}

bool PhoneSystem::handleEvent(const sf::Event &event,
                              const sf::RenderWindow &window) {
  (void)window; // Unused parameter warning fix

  if (mState == Ringing) {
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
      sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x),
                            static_cast<float>(event.mouseButton.y));

      // Check collision with the sprite/rect
      sf::FloatRect bounds(
          mSprite.getPosition(),
          sf::Vector2f(100.f, 100.f)); // Hardcoded size for now

      if (bounds.contains(mousePos)) {
        std::cout << "Input: Phone Clicked!" << std::endl;
        mState = Talking;
        time = sf::Time::Zero;
        return true;
      }
    }
  }
  return false;
}

GameID::Malus PhoneSystem::getRequiredMask() const { return mRequiredMask; }

void PhoneSystem::draw(sf::RenderTarget &target,
                       sf::RenderStates states) const {
  // Temporary drawing logic until textures are ready
  sf::RectangleShape rect(sf::Vector2f(100.f, 100.f));
  rect.setPosition(mSprite.getPosition());
  rect.setFillColor(mSprite.getColor());

  // Pulse effect when ringing
  if (mState == Ringing) {
    if (static_cast<int>(time.asSeconds() * 10) % 2 == 0) {
      rect.setFillColor(sf::Color::Yellow);
    }
  }

  target.draw(rect, states);
  target.draw(mSubtitleText, states);
}

bool PhoneSystem::isWaitingForMask() const {
  // We are waiting if the call is done and we identified a threat
  return mState == Finished && mRequiredMask != GameID::Malus::None;
}

bool PhoneSystem::isCallFinished() const { return mState == Finished; }

void PhoneSystem::reset() {
  mState = Idle;
  time = sf::Time::Zero;
  mRequiredMask = GameID::Malus::None;
  mSubtitleText.setString("");
}

// --- MASK SELECTOR ---

MaskSelector::MaskSelector(Context context) {
  (void)context; // context used later for textures

  mButtons.clear();

  float y = 100.f;      // position de départ
  float offsetY = 70.f; // écart vertical entre boutons
  float width = 150.f;
  float height = 50.f;

  // List of available masks
  std::vector<GameID::Malus> availableMasks = {
      GameID::Malus::Alcool, GameID::Malus::Stinky, GameID::Malus::Headset,
      GameID::Malus::Coke, GameID::Malus::Fat};

  for (auto malus : availableMasks) {
    Button btn;
    btn.isSelected = false;
    btn.maskID = malus;

    // Position the button
    btn.sprite.setPosition(100.f, y);

    // Assign Colors for prototype visualization
    switch (malus) {
    case GameID::Malus::Alcool:
      btn.sprite.setColor(sf::Color::Red);
      break;
    case GameID::Malus::Stinky:
      btn.sprite.setColor(sf::Color::Green);
      break;
    case GameID::Malus::Headset:
      btn.sprite.setColor(sf::Color::Blue);
      break;
    case GameID::Malus::Coke:
      btn.sprite.setColor(sf::Color::Cyan);
      break;
    case GameID::Malus::Fat:
      btn.sprite.setColor(sf::Color::Magenta);
      break;
    default:
      btn.sprite.setColor(sf::Color::White);
      break;
    }

    // Store dimensions in the sprite logic (even without texture)
    // This is a hack for clickable area without texture
    btn.sprite.setTextureRect(
        sf::IntRect(0, 0, static_cast<int>(width), static_cast<int>(height)));

    mButtons.push_back(btn);
    y += offsetY;
  }
}

void MaskSelector::handleEvent(const sf::Event &event) {
  if (event.type != sf::Event::MouseButtonPressed ||
      event.mouseButton.button != sf::Mouse::Left)
    return;

  sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x),
                        static_cast<float>(event.mouseButton.y));

  for (auto &button : mButtons) {
    // Manually check bounds because sprite texture rect might be weird without
    // real texture
    sf::FloatRect bounds(button.sprite.getPosition(),
                         sf::Vector2f(150.f, 50.f));

    if (bounds.contains(mousePos)) {
      // Deselect others
      for (auto &b : mButtons)
        b.isSelected = false;

      // Select this one
      button.isSelected = true;
      std::cout << "Mask Selected: " << static_cast<int>(button.maskID)
                << std::endl;
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

void MaskSelector::draw(sf::RenderTarget &target,
                        sf::RenderStates states) const {
  for (const auto &button : mButtons) {
    // Draw the colored rectangle
    sf::RectangleShape rect(sf::Vector2f(150.f, 50.f));
    rect.setPosition(button.sprite.getPosition());
    rect.setFillColor(button.sprite.getColor());

    // Highlight if selected
    if (button.isSelected) {
      rect.setOutlineThickness(3.f);
      rect.setOutlineColor(sf::Color::Yellow);
    } else {
      rect.setOutlineThickness(0.f);
    }

    target.draw(rect, states);
  }
}

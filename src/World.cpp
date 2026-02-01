#include "../include/World.hpp"
#include "../include/PlayerCar.hpp" // <--- The compiler sees the full class here
#include <iostream>

// <--- NEW: Define the destructor here
World::~World() = default;

World::World(Context context)
    : mContext(context), mWindow(*context.window),
      mWorldView(context.window->getDefaultView()),
      mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 20000.f) // Long road
      ,
      mSpawnPosition(mWorldView.getSize().x / 2.f,
                     mWorldView.getSize().y - 200.f),
      mScrollSpeed(0.f), mPlayerCar(nullptr) {
  // 1. Setup Road (From Jonas's logic: centered rectangle)
  sf::Vector2f roadSize(400.f, mWorldView.getSize().y);
  sf::Vector2f roadPos(mWorldView.getSize().x / 2.f,
                       mWorldView.getSize().y / 2.f);

  mRoadRect.setSize(roadSize);
  mRoadRect.setOrigin(roadSize / 2.f);
  mRoadRect.setPosition(roadPos);
  mRoadRect.setFillColor(sf::Color(50, 50, 50)); // Dark Grey Road
  mRoadRect.setOutlineThickness(5.f);
  mRoadRect.setOutlineColor(sf::Color::White);

  // Define borders for collision (Left X, Right X)
  // Area = Center - HalfWidth to Center + HalfWidth
  mRoadBorders =
      std::make_tuple(roadPos - (roadSize / 2.f), roadPos + (roadSize / 2.f));

  // 2. Setup Player
  mPlayerCar.reset(new PlayerCar(*context.assets));
  mPlayerCar->setPosition(mSpawnPosition);
}

void World::update(sf::Time dt) {
  // 1. Handle Input (Steering)
  mPlayerCar->handleRealtimeInput(*mContext.input);

  // 2. Update Physics (pass road borders to limit movement)
  mPlayerCar->update(dt, mRoadBorders);

  // 3. Scroll Logic (Fake movement)
  // In a vertical scroller, we often just move obstacles down
  // But for now, we just update the car.
}

void World::draw() {
  mWindow.setView(mWorldView);
  // Render scene to image for post-processing
  sf::RenderTexture renderTex;
  renderTex.create(static_cast<unsigned int>(mWorldView.getSize().x), static_cast<unsigned int>(mWorldView.getSize().y));
  renderTex.clear();
  renderTex.draw(mRoadRect);
  renderTex.draw(*mPlayerCar);
  renderTex.display();

  // Apply effect chain if available
  sf::Image sceneImage = renderTex.getTexture().copyToImage();
  sf::Image processedImage;
  if (mContext.session) {
    float t = mEffectClock.getElapsedTime().asSeconds();
    mContext.session->effectChain.apply(sceneImage, processedImage, t);
  } else {
    processedImage = sceneImage;
  }

  // Draw processed image to window
  sf::Texture finalTex;
  finalTex.loadFromImage(processedImage);
  sf::Sprite finalSprite(finalTex);
  mWindow.draw(finalSprite);

  // Debug overlay: list enabled effects
  if (mContext.session && mContext.assets) {
    auto names = mContext.session->effectChain.getEnabledNames();
    sf::Text text;
    text.setFont(mContext.assets->get(GameID::Font::Main));
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(2.f);
    if (names.empty()) {
      text.setString("Effects: none");
    } else {
      std::string line = "Effects: ";
      for (size_t i = 0; i < names.size(); ++i) {
        line += names[i];
        if (i + 1 < names.size()) line += ", ";
      }
      text.setString(line);
    }
    text.setPosition(16.f, 16.f);
    mWindow.draw(text);
  }
}

bool World::hasCrashed() const {
  return false; // TODO: Implement obstacle collision
}

bool World::hasReachedDestination() const {
  return false; // TODO: Timer or Distance
}

void World::handleCollisions() {
  // Placeholder
}

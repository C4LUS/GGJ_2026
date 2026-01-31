#include "../include/world.hpp"
#include <algorithm>

namespace {
enum Layer { Background, Road, Air, LayerCount };

class RectangleNode final : public SceneNode {
public:
  RectangleNode(sf::Vector2f size, sf::Color color) : mShape(size) {
    mShape.setFillColor(color);
  }

private:
  void drawCurrent(sf::RenderTarget &target,
                   sf::RenderStates states) const override {
    target.draw(mShape, states);
  }

  sf::RectangleShape mShape;
};
} // namespace

World::World(Context context)
    : mContext(context), mWindow(*context.window), mSceneGraph(),
      mSceneLayers(), mPlayer(nullptr), mMalusManager(), mTrafficCars(),
      mWorldBounds({0.f, 0.f},
                   {static_cast<float>(mWindow.getSize().x),
                    static_cast<float>(mWindow.getSize().y)}),
      mScrollSpeed(160.f) {
  buildScene();
  if (mContext.session) {
    mMalusManager.loadFromSession(*mContext.session);
  }
}

void World::update(sf::Time dt) {
  if (mContext.input && mPlayer) {
    if (mContext.input->isActionActive(GameID::Action::SteerLeft)) {
      mPlayer->handleRealtimeInput(
          mMalusManager.processInput(GameID::Action::SteerLeft));
    }
    if (mContext.input->isActionActive(GameID::Action::SteerRight)) {
      mPlayer->handleRealtimeInput(
          mMalusManager.processInput(GameID::Action::SteerRight));
    }
    if (mContext.input->isActionActive(GameID::Action::Accelerate)) {
      mPlayer->handleRealtimeInput(
          mMalusManager.processInput(GameID::Action::Accelerate));
    }
    if (mContext.input->isActionActive(GameID::Action::Brake)) {
      mPlayer->handleRealtimeInput(
          mMalusManager.processInput(GameID::Action::Brake));
    }
  }

  mSceneGraph.update(dt);

  if (mPlayer) {
    sf::Vector2f pos = mPlayer->getWorldPosition();
    pos.x = std::clamp(pos.x, mWorldBounds.position.x,
                       mWorldBounds.position.x + mWorldBounds.size.x);
    pos.y = std::clamp(pos.y, mWorldBounds.position.y,
                       mWorldBounds.position.y + mWorldBounds.size.y);
    mPlayer->setPosition(pos);
  }

  for (auto *traffic : mTrafficCars) {
    const sf::Vector2f size = traffic->getSize();
    const float halfHeight = size.y * 0.5f;
    const float bottom = mWorldBounds.position.y + mWorldBounds.size.y;
    if (traffic->getWorldPosition().y - halfHeight > bottom) {
      traffic->setPosition({traffic->getWorldPosition().x,
                            mWorldBounds.position.y - halfHeight});
    }
  }

  handleCollisions();
}

void World::draw() {
  mWindow.draw(mSceneGraph);
  mMalusManager.drawEffects(mWindow);
}

bool World::hasReachedDestination() const { return false; }

bool World::hasCrashed() const { return false; }

void World::handleCollisions() {
  // TODO: check collisions between player and traffic/obstacles.
}

void World::buildScene() {
  for (std::size_t i = 0; i < LayerCount; ++i) {
    auto layer = std::make_unique<SceneNode>();
    mSceneLayers[i] = layer.get();
    mSceneGraph.attachChild(std::move(layer));
  }

  auto background = std::make_unique<RectangleNode>(
      mWorldBounds.size, sf::Color(18, 18, 18));
  mSceneLayers[Background]->attachChild(std::move(background));

  const float roadWidth = mWorldBounds.size.x * 0.55f;
  auto road = std::make_unique<RectangleNode>(
      sf::Vector2f(roadWidth, mWorldBounds.size.y), sf::Color(50, 50, 50));
  road->setPosition({(mWorldBounds.size.x - roadWidth) * 0.5f, 0.f});
  mSceneLayers[Road]->attachChild(std::move(road));

  if (mContext.textures) {
    auto player = std::make_unique<PlayerCar>(*mContext.textures);
    mPlayer = player.get();
    mPlayer->setPosition({mWorldBounds.size.x * 0.5f,
                          mWorldBounds.size.y * 0.8f});
    mSceneLayers[Air]->attachChild(std::move(player));
  }

  const float laneLeft = mWorldBounds.size.x * 0.5f - roadWidth * 0.2f;
  const float laneRight = mWorldBounds.size.x * 0.5f + roadWidth * 0.2f;

  auto makeTraffic = [&](sf::Vector2f position, sf::Color color) {
    auto car = std::make_unique<TrafficCar>(sf::Vector2f(44.f, 72.f), color);
    TrafficCar *ptr = car.get();
    ptr->setPosition(position);
    ptr->setVelocity({0.f, mScrollSpeed});
    mTrafficCars.push_back(ptr);
    mSceneLayers[Air]->attachChild(std::move(car));
  };

  makeTraffic({laneLeft, mWorldBounds.size.y * 0.2f},
              sf::Color(200, 70, 70));
  makeTraffic({laneRight, mWorldBounds.size.y * 0.05f},
              sf::Color(200, 200, 70));
  makeTraffic({laneLeft, mWorldBounds.size.y * -0.2f},
              sf::Color(70, 140, 220));
}

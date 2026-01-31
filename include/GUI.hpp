#pragma once
#include "GameId.hpp"
#include "SharedContext.hpp" // To get Fonts/Textures
#include <SFML/Graphics.hpp>
#include <functional>

namespace GUI {

class Button : public sf::Drawable, public sf::Transformable {
public:
  typedef std::shared_ptr<Button> Ptr;
  typedef std::function<void()> Callback;

  Button(const FontHolder &fonts, const TextureHolder &textures);

  void setCallback(Callback callback);
  void setText(const std::string &text);
  void setToggle(bool flag); // If true, button stays pressed (useful for Masks)

  // Used to detect clicks
  void handleEvent(const sf::Event &event, const sf::RenderWindow &window);

  // Visual State
  bool isSelected() const; // Is mouse hovering?
  void select();
  void deselect();
  void activate(); // Trigger the callback manually
  void deactivate();

private:
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;
  void changeTexture(
      GameID::Texture::Type type); // Helper to swap normal/pressed textures

private:
  Callback mCallback;
  sf::Sprite mSprite;
  sf::Text mText;
  bool mIsToggle;
  bool mIsSelected;
  bool mIsActive;

  const TextureHolder &mTextures; // Reference to hold textures
};

} // namespace GUI

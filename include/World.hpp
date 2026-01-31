#pragma once
#include "SharedContext.hpp"
#include <SFML/Graphics.hpp>
#include "Character.hpp"
#include "SharedContext.hpp"
#include <memory>

class World {
public:
    explicit World(Context context);
    ~World();

    void update(sf::Time dt);
    void draw();

private:
    Context mContext;
    sf::RenderWindow& mWindow;

    // On utilise unique_ptr pour gérer la mémoire proprement
    std::unique_ptr<Character> mPlayer;
};

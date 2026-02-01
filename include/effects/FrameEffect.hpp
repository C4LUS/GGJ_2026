// Moved from malus/effects/FrameEffect.hpp for integration
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include "../GameId.hpp"

class FrameEffect {
public:
    FrameEffect(std::string name = "") : name(std::move(name)) {}
    virtual ~FrameEffect() = default;

    virtual void apply(const sf::Image& src, sf::Image& dst, float time = 0.f) = 0;

    void setEnabled(bool e) { enabled = e; }
    bool isEnabled() const { return enabled; }
    const std::string& getName() const { return name; }
    void setName(const std::string& n) { name = n; }

private:
    bool enabled{true};
    std::string name;
};

class EffectChain {
public:
    using Ptr = std::unique_ptr<FrameEffect>;

    void addEffect(GameID::Malus type, Ptr effect) {
        effects[type] = std::move(effect);
    }

    void setEnabled(GameID::Malus type, bool e) {
        auto it = effects.find(type);
        if (it != effects.end()) it->second->setEnabled(e);
    }
    bool isEnabled(GameID::Malus type) const {
        auto it = effects.find(type);
        return it != effects.end() ? it->second->isEnabled() : false;
    }
    void toggle(GameID::Malus type) {
        auto it = effects.find(type);
        if (it != effects.end()) it->second->setEnabled(!it->second->isEnabled());
    }
    FrameEffect* getEffect(GameID::Malus type) {
        auto it = effects.find(type);
        return it != effects.end() ? it->second.get() : nullptr;
    }
    const FrameEffect* getEffect(GameID::Malus type) const {
        auto it = effects.find(type);
        return it != effects.end() ? it->second.get() : nullptr;
    }
    void setAllDisabled() {
        for (auto& pair : effects) pair.second->setEnabled(false);
    }
    void apply(const sf::Image& src, sf::Image& out, float time = 0.f) {
        if (effects.empty()) { out = src; return; }
        sf::Image a = src;
        sf::Image b;
        for (int i = static_cast<int>(GameID::Malus::None); i <= static_cast<int>(GameID::Malus::MixedControls); ++i) {
            auto it = effects.find(static_cast<GameID::Malus>(i));
            if (it != effects.end() && it->second->isEnabled()) {
                it->second->apply(a, b, time);
                a = std::move(b);
            }
        }
        out = std::move(a);
    }
private:
    std::map<GameID::Malus, Ptr> effects;
};

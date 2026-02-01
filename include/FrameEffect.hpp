#ifndef FRAME_EFFECT_HPP
#define FRAME_EFFECT_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include "GameId.hpp"


// Abstract base class for frame/post-processing effects.
class FrameEffect {
    public:
        FrameEffect(std::string name = "") : name(std::move(name)) {}
        virtual ~FrameEffect() = default;

        // Apply the effect to `src`, writing into `dst`.
        // `time` may be used for animated effects (seconds).
        virtual void apply(const sf::Image& src, sf::Image& dst, float time = 0.f) = 0;

        // Optional hooks for non-visual effects
        virtual void onEnable() {}
        virtual void onDisable() {}

        void setEnabled(bool e) {
            if (enabled == e) return;
            enabled = e;
            if (enabled) onEnable();
            else onDisable();
        }
        bool isEnabled() const { return enabled; }
        const std::string& getName() const { return name; }
        void setName(const std::string& n) { name = n; }

    private:
        bool enabled{true};
        std::string name;
};

// A container that applies a sequence of effects one after another.

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
    void setAllEnabled() {
        for (auto& pair : effects) pair.second->setEnabled(true);
    }
    std::vector<std::string> getEnabledNames() const {
        std::vector<std::string> names;
        for (const auto &pair : effects) {
            if (pair.second && pair.second->isEnabled()) {
                names.push_back(pair.second->getName());
            }
        }
        return names;
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

#endif // FRAME_EFFECT_HPP

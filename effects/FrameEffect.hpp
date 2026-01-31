#ifndef FRAME_EFFECT_HPP
#define FRAME_EFFECT_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>


// Abstract base class for frame/post-processing effects.
class FrameEffect {
public:
    FrameEffect(std::string name = "") : name(std::move(name)) {}
    virtual ~FrameEffect() = default;

    // Apply the effect to `src`, writing into `dst`.
    // `time` may be used for animated effects (seconds).
    virtual void apply(const sf::Image& src, sf::Image& dst, float time = 0.f) = 0;

    void setEnabled(bool e) { enabled = e; }
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

    void addEffect(Ptr effect) { effects.push_back(std::move(effect)); }

    // Enable/disable by index
    void setEnabled(size_t idx, bool e) {
        if (idx < effects.size()) effects[idx]->setEnabled(e);
    }
    bool isEnabled(size_t idx) const {
        return idx < effects.size() ? effects[idx]->isEnabled() : false;
    }

    // Enable/disable by name (first match)
    bool setEnabled(const std::string& name, bool e) {
        for (auto& ex : effects) {
            if (ex->getName() == name) { ex->setEnabled(e); return true; }
        }
        return false;
    }
    bool isEnabled(const std::string& name) const {
        for (auto& ex : effects) if (ex->getName() == name) return ex->isEnabled();
        return false;
    }

    // Toggle by name
    bool toggle(const std::string& name) {
        for (auto& ex : effects) if (ex->getName() == name) { ex->setEnabled(!ex->isEnabled()); return true; }
        return false;
    }

    // Access effect pointer by name (non-owning). Returns nullptr if not found.
    FrameEffect* getEffect(const std::string& name) {
        for (auto& ex : effects) if (ex->getName() == name) return ex.get();
        return nullptr;
    }
    const FrameEffect* getEffect(const std::string& name) const {
        for (auto& ex : effects) if (ex->getName() == name) return ex.get();
        return nullptr;
    }

    // Apply all enabled effects in order. `src` is the input image, result written to `out`.
    void apply(const sf::Image& src, sf::Image& out, float time = 0.f) {
        if (effects.empty()) { out = src; return; }

        // Temporary buffers for ping-ponging.
        sf::Image a = src;
        sf::Image b;
        for (auto& e : effects) {
            if (!e->isEnabled()) continue;
            e->apply(a, b, time);
            a = std::move(b);
        }
        out = std::move(a);
    }

private:
    std::vector<Ptr> effects;
};

#endif // FRAME_EFFECT_HPP

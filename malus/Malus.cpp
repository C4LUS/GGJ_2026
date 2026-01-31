#include "Malus.hpp"
#include <algorithm>
#include <array>

Malus::Malus() {}

void Malus::add(Type type, int amount) {
    counts[type] += amount;
}

void Malus::setHandler(Type type, MalusFunc func) {
    handlers[type] = func;
}

void Malus::run() {
    if (counts.empty()) return;
    // Compute squared weights
    std::vector<Type> types;
    std::vector<int> weights;
    int totalWeight = 0;
    for (const auto& pair : counts) {
        int w = pair.second * pair.second;
        if (w > 0) {
            types.push_back(pair.first);
            weights.push_back(w);
            totalWeight += w;
        }
    }
    if (types.empty() || totalWeight == 0) return;
    // Weighted random selection
    int r = rand() % totalWeight;
    int acc = 0;
    Type chosen = types[0];
    for (size_t i = 0; i < types.size(); ++i) {
        acc += weights[i];
        if (r < acc) {
            chosen = types[i];
            break;
        }
    }
    // Trigger the handler if set
    auto it = handlers.find(chosen);
    if (it != handlers.end()) {
        it->second();
    }
}

void Malus::clear() {
    counts.clear();
}

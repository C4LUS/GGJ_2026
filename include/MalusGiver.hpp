#pragma once
#include <functional>
#include <map>
#include <algorithm>

class MalusGiver {
public:
    enum Type {
        Blur,
        Grayscale,
        Wave,
        Shake,
        Reverse,
        Split,
        MixedControls,
        Count
    };

    using MalusFunc = std::function<void()>;

    MalusGiver();

    void add(Type type, int amount = 1);
    void setHandler(Type type, MalusFunc func);
    void run();
    void clear();

private:
    std::map<Type, int> counts;
    std::map<Type, MalusFunc> handlers;
};

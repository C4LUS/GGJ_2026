
#pragma once

#include "ObstacleGoat.hpp"
#include "ObstacleGuy.hpp"
#include "ObstacleWood.hpp"
#include "ObstacleCustomizable.hpp"
#include <memory>

class ObstacleFactory
{
    public:
        static std::unique_ptr<IObstacle> CreateObstacle(ObstacleType type)
        {
            if (type == WOOD)
                return CreateWood();
            if (type == GOAT)
                return CreateGoat();
            if (type == GUY)
                return CreateGuy();
            return CreateCustomizable();
        }
    
    private:
        static std::unique_ptr<IObstacle> CreateWood()
        {
            return std::make_unique<ObstacleWood>(WOOD_POS, WOOD_SIZE);
        }

        static std::unique_ptr<IObstacle> CreateGoat()
        {
            return std::make_unique<ObstacleGoat>(GOAT_POS, GOAT_SIZE);
        }

        static std::unique_ptr<IObstacle> CreateGuy()
        {
            return std::make_unique<ObstacleWood>(GUY_POS, GUY_SIZE);
        }

        static std::unique_ptr<IObstacle> CreateCustomizable()
        {
            return std::make_unique<ObstacleCustomizable>(WOOD_POS, WOOD_SIZE);
        }
};
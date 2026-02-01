
#pragma once

#include <memory>
#include "ObstacleGoat.hpp"
#include "ObstacleGuy.hpp"
#include "ObstacleWood.hpp"
#include "ObstacleVan.hpp"
#include "ObstacleBike.hpp"
#include "ObstacleCar.hpp"
#include "ObstacleBus.hpp"
#include "ObstacleCustomizable.hpp"

class ObstacleFactory
{
    public:
        static std::unique_ptr<IObstacle> CreateObstacle(ObstacleType type)
        {
            if (type == WOOD)
                return createWood();
            if (type == GOAT)
                return createGoat();
            if (type == GUY)
                return createGuy();
            if (type == CAR)
                return createCar();
            if (type == VAN)
                return createVan();
            if (type == BUS)
                return createBus();
            if (type == BIKE)
                return createBike();
            return createCustomizable();
        }
    
    private:
        static std::unique_ptr<IObstacle> createWood()
        {
            return std::make_unique<ObstacleWood>(OBSTACLE_POS, WOOD_SIZE);
        }

        static std::unique_ptr<IObstacle> createGoat()
        {
            return std::make_unique<ObstacleGoat>(OBSTACLE_POS, GOAT_SIZE);
        }

        static std::unique_ptr<IObstacle> createGuy()
        {
            return std::make_unique<ObstacleWood>(OBSTACLE_POS, GUY_SIZE);
        }

        static std::unique_ptr<IObstacle> createCustomizable()
        {
            return std::make_unique<ObstacleCustomizable>(OBSTACLE_POS, CUSTOMIZABLE_SIZE);
        }

        static std::unique_ptr<IObstacle> createCar()
        {
            return std::make_unique<ObstacleCar>(OBSTACLE_POS, CAR_SIZE);
        }

        static std::unique_ptr<IObstacle> createVan()
        {
            return std::make_unique<ObstacleVan>(OBSTACLE_POS, VAN_SIZE);
        }

        static std::unique_ptr<IObstacle> createBus()
        {
            return std::make_unique<ObstacleCustomizable>(OBSTACLE_POS, BUS_SIZE);
        }

        static std::unique_ptr<IObstacle> createBike()
        {
            return std::make_unique<ObstacleCustomizable>(OBSTACLE_POS, BIKE_SIZE);
        }
};

#pragma once

    #include "ObstacleFactory.hpp"
    #include "Car.hpp"
    #include <cstdlib>
    #include <ctime>
    #include <vector>

class ObstacleSpawner
{
    public:
        ObstacleSpawner(ObstacleFactory& obstacle_factory) : _obstacle_factory(obstacle_factory)
        {
            this->_obstacle_vector = std::vector<std::unique_ptr<IObstacle>>(0);
        }

        void spawnObstacle(sf::RenderWindow& window, Car &car)
        {
            while (this->_obstacle_vector.size() <= 3) {
                pushObstacle();
            }

            if (this->_obstacle_vector[0]->getDisplay() == false) {
                this->_obstacle_vector[0]->setDisplay(true);
                this->_obstacle_vector[0]->randomizePos();
            }
            
            if (this->_obstacle_vector[0]->is_alive()) {
                this->_obstacle_vector[0]->is_collide(car);
                this->_obstacle_vector[0]->moveObstacle(5);
                this->_obstacle_vector[0]->Display(window);
            } else {
                popObstacle();
                pushObstacle();
            }
        }

        void pushObstacle()
        {
            int type = rand() % 4;

            if (type == WOOD)
                this->_obstacle_vector.push_back(this->_obstacle_factory.CreateObstacle(WOOD));
            if (type == GUY)
                this->_obstacle_vector.push_back(this->_obstacle_factory.CreateObstacle(GUY));
            if (type == GOAT)
                this->_obstacle_vector.push_back(this->_obstacle_factory.CreateObstacle(GOAT));
            this->_obstacle_vector.push_back(this->_obstacle_factory.CreateObstacle(CUSTOMIZABLE));
        }

        void popObstacle()
        {
            this->_obstacle_vector.erase(this->_obstacle_vector.begin());
        }

        ObstacleFactory& getObstacleFactory() const
        {
            return this->_obstacle_factory;
        }
        

    private:
        ObstacleFactory& _obstacle_factory;
        std::vector<std::unique_ptr<IObstacle>> _obstacle_vector;
};
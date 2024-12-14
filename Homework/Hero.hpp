#ifndef HERO_HPP
#define HERO_HPP

#include "Main.hpp"
#include "Entity.hpp"

class Hero : public Ent::Entity{
    public:
        Hero(Attribute atr, Point pos, int **&field, int id) : Entity(atr, pos, field, id, 1) {}

        std::vector<Point> move(Point finish) {
            if (short_path(field, used, paths, pos, finish)) return {};
            std::vector<Point> path;

            for (Point point : make_path(paths, pos, finish)) {
                if (!(this -> decP())) break;
                path.push_back(point);
            }

            if (!path.empty()) this -> Drag(path.back());
            return path;
        }

        std::vector<Point> MakeMove() override {return {};}
};






#endif
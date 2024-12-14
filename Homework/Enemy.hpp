#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Main.hpp"
#include "Hero.hpp"
#include "Entity.hpp"

class Enemy : public Ent::Entity{
    Matrix<int> dist;
    Entity *target;

    public:
        Enemy(Attribute atr, Point pos, int **&field, int id) : Entity(atr, pos, field, id, 2) {
            dist.resize(M, std::vector<int> (N)); 
            target = nullptr;
            }

        void setTarget(Hero *&target) {this -> target = target;}

        std::vector<Point> MakeMove() override {
            std::vector<Point> path, circle;

            Point min_p;
            int min_dist = (M * N);

            int x, y;
            int R = 1;

            make_way_matrix(field, used, paths, dist, pos);

            //try going very close
            do {
                circle = make_circle(target -> getPos(), R++);

                for (Point p : circle) {
                    p.fill(x, y);
                    if (dist[y][x] == -1) continue;
                    if (dist[y][x] < min_dist) {min_p = p; min_dist = dist[y][x];};
                }

                if (!min_p.is_none() && (this -> decP(min_dist))) {
                    path = make_path(paths, pos, min_p);

                    this -> Drag(min_p);
                    break;
                }
            } while (!circle.empty());

            //atack
            while (this -> Atack(target)) {std::cout << "atacking" << std::endl;}
            return path;
        }
};


#endif
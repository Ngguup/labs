#ifndef ENTITY
#define ENTITY

#include "Main.hpp"

struct Attribute {
    int str, dex, con;
};

namespace Ent {
    class Entity {
        protected:
            int type;
            int id;

            Attribute atr;

            int Max_hp, hp;
            int Max_points, points;
            int initiative;

            Point pos;
            int **field;

            Matrix<bool> used;
            Matrix<Point> paths;
        public:
            Entity() {hp = 0;}
            Entity(Attribute atr, Point pos, int **&field, int id, int type = 0) {
                this -> type = type;
                this -> id = id;

                used.resize(M, std::vector<bool> (N));
                paths.resize(M, std::vector<Point> (N));

                this -> field = field;
                this -> atr = atr;
                this -> pos = pos;

                Max_hp = atr.con;
                hp = Max_hp;
                initiative = 0;

                Max_points = atr.dex;
                points = Max_points;

                this -> fillCell(id);
            }

            bool Atack(Entity *&target) {
            //atak statsHero
                int atackRadious = 1, atackDemage = 1, atackCost = 1;
            //

                if ((Distance(pos, target -> getPos()) <= atackRadious) && (this -> decP(atackCost))) {
                    target -> decHP(atackDemage);
                    return true;
                }
                return false;
            }

            void fillCell(int cell) {field[pos.getY()][pos.getX()] = cell;}
            void Drag(Point pos) {
                this -> fillCell(0);
                this -> pos = pos;
                this -> fillCell(id);
            }

            virtual int throwInitiative() {initiative = atr.dex; return initiative;}
            void recover() {points = Max_points;}

            void setPos(Point pos) {this -> pos = pos;}

            int getInitiative() {return initiative;}
            Point getPos() {return pos;}
            int getHP() {return hp;}

            int getType() {return type;}
            int getId() {return id;}

            bool decP(int n = 1) {
                if (points - n < 0) return false;
                points -= n;
                return true;
            }
            void decHP(int n) {
                if (hp - n <= 0) hp = 0;
                else hp -= n;
            }

            virtual std::vector<Point> MakeMove() = 0;
    };
}

#endif
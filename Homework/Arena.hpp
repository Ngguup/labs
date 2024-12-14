#ifndef ARENA
#define ARENA

#include "Main.hpp"
#include "Entity.hpp"
#include "Hero.hpp"
#include "Enemy.hpp"

namespace Arena {
    class Arena {
        std::list<int> queue;
        std::map<int, Ent::Entity*> entities;
        //std::map<Point, int> posId;

        int **field;

        int currentId;

        int heroId;
        Hero *currentHero;

        void changeId() {
            currentId++;
        }

        int posId(Point pos) {return field[pos.getY()][pos.getX()];}

        public:
            Arena(int **&field) {
                this -> field = field; 
                currentId = 0; 
                heroId = -1; 
                currentHero = nullptr;
            }

            ~Arena() {
                for (auto iter = queue.begin(); iter != queue.end(); iter++) {
                    delete entities[*iter];
                    entities.erase(*iter);
                }
            }

            void addEntity(int type, Point pos) {
                this -> changeId();

                //posId[pos] = currentId;

                switch (type)
                {
                case 1:
                    entities[currentId] = new Hero({5, 5, 5}, pos, field, currentId);
                    break;
                case 2:
                    entities[currentId] = new Enemy({4, 4, 4}, pos, field, currentId);
                    break;
                
                default:
                    break;
                }
                
                int initiative = entities[currentId] -> throwInitiative();

                if (entities[currentId] -> getType() == 1) {
                    if (heroId == -1 || initiative > entities[heroId] -> getInitiative()) {
                        heroId = currentId;
                        currentHero = dynamic_cast<Hero*>(entities[currentId]);
                    }
                }

                

                bool flag = true;
                for (auto iter = queue.begin(); iter != queue.end(); iter++) {
                    if (initiative < entities[*iter] -> getInitiative()) {
                        flag = false;
                        queue.insert(iter, currentId);
                        break;
                     }
                }
                if (flag) queue.push_back(currentId);
            }

            std::vector<Point> MakeMove() {
                if (entities[queue.back()] -> getType() == 1) return {};
                if (heroId == -1) {this -> turn(); return {};}

                Enemy *enemy = dynamic_cast<Enemy*>(entities[queue.back()]);
                Point pos = enemy -> getPos();

                enemy -> setTarget(currentHero);
                std::vector path = enemy -> MakeMove();

                //this -> changePos(pos);
                this -> turn();
                return path;
            }

            bool Atack(Point pos) {
                if (!entities.count(posId(pos))) return false;
                int id = posId(pos);

                Ent::Entity *target = entities[id];
                if (currentHero -> Atack(target)) {
                    if (target -> getHP() == 0) {
                        target -> fillCell(0);
                        delete target;

                        entities.erase(id);
                        field[pos.getY()][pos.getX()] = 0;

                        for (auto iter = queue.begin(); iter != queue.end(); iter++) {
                            if (*iter == id) {
                                queue.erase(iter);
                                break;
                            }
                        }
                    }
                    return true;
                }
                return false;
                
            }

            std::vector<Point> move(Point pos) {
                if (this -> type() != 1) return {};

                //Point lastPos = currentHero -> getPos();
                std::vector<Point> path = currentHero -> move(pos);
                //this -> changePos(lastPos);

                return path;
            }

            int getHP() {return currentHero -> getHP();}

            void turn() {
                int id = queue.back();
                queue.pop_back();
                queue.push_front(id);

                id = queue.back();
                entities[id] -> recover();

                if (entities[id] -> getType() == 1) {
                    heroId = id;
                    currentHero = dynamic_cast<Hero*>(entities[heroId]);
                }
            }

            /*
            bool changePos(Point pos) {
                if (!posId.count(pos)) return false;

                int id = posId[pos];
                posId.erase(pos);
                posId[entities[id] -> getPos()] = id;
                return true;
            }*/

            int type() {return entities[queue.back()] -> getType();}
    };
}



#endif
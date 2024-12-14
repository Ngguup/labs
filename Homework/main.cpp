#include "Main.hpp"


int main() {
    int **field;
    read("field.txt", field);

    Arena::Arena arena(field);
    arena.addEntity(1, {0, 0});
    arena.addEntity(2, {5, 0});
    //arena.addEntity(2, {5, 1});

    print(field);
    std::cout << "Current HP: " << arena.getHP() << std::endl;
    std::cout << std::endl << std::endl;

    while (true) {
        while(arena.type() == 2) arena.MakeMove();
        if (!arena.getHP()) break;

        print(field);
        std::cout << "Current HP: " << arena.getHP() << std::endl;
        std::cout << std::endl << std::endl;

        char key;
        int x, y;

        while(true) {
            std::cin >> key;
            if (key == 't') {arena.turn(); break;}

            std::cin >> x;
            std::cin >> y;

            switch (key)
            {
            case 'a':
                arena.Atack({x, y});
                break;
            case 'm':
                arena.move({x, y});
                print(field);
                std::cout << std::endl << std::endl;
                break;
        
            default:
                break;
            }
        }
    }
    std::cout << "Game Over" << std::endl;
    

    return 0;
}
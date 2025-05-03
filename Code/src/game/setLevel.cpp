//
// Created by Gabriel on 5/3/2025.
//

#include "../../include/game/gameFunction.h"

void game::setLevel(int k) {
    std::string filename = "../Code/Levels/level" + std::to_string(k) + ".txt";
    std::ifstream f(filename);
    std::string line;
    level.clear();
    try {
        if (!f.is_open()) {
            throw FileException(filename);
        }
    } catch (const FileException &txt) {
        std::cout << txt.what() << std::endl;
        exit(0);
    }
    // 0 liber
    // 1 brick
    // P player
    // 2 tortoise
    int n = 1;

    while (std::getline(f, line)) {
        for (long long unsigned int i = 0; i < line.length(); i++) {
            {
                std::shared_ptr<Entity> a;
                try {
                    if (line[i] == '1') {
                        a = std::make_shared<Brick>((i) * 64, n * 64);
                        throw(a);
                    } else if (line[i] == '2') {
                        a = std::make_shared<Turtle>((i) * 64, n * 64);
                        throw(a);
                    } else if (line[i] == 'P') {
                        a = std::make_shared<Player>((i) * 64, n * 64);
                        throw(a);
                    } else if (line[i] != '0')
                        throw(BaseException("Nu exista aceasta entitate"));
                } catch (const BaseException &txt) {
                    std::cout << txt.what() << std::endl;
                    exit(0);
                }
                catch (...) {
                    level.push_back(a);
                }
            }
        }
        n++;
    }
    f.close();
    level.sort([](const std::shared_ptr<Entity> &a, const std::shared_ptr<Entity> &b) -> bool {
        return a->coord_x() < b->coord_x();
    });
}

void game::setEntities() {
    entities.clear();
    environment.clear();
    /*
    for (int i = 0; i < screenHeight; i ++)
        for (int j = 0; j < screenWidth; j ++)
            grid[i][j] = nullptr;
            */
    for (auto entity: level) {
        if (std::dynamic_pointer_cast<Living>(entity) != nullptr) {
            try {
                entities.push_back(std::dynamic_pointer_cast<Living>(entity));
            } catch (TextureException &txt) {
                std::cout << txt.what() << std::endl;
                exit(0);
            }
        } else {
            try {
                environment.push_back(std::dynamic_pointer_cast<Environment>(entity));
            } catch (TextureException &txt) {
                std::cout << txt.what() << std::endl;
                exit(0);
            }
        }
        //  insertEntity(entity);
    }
    bool ok;
    ok = true;
}

//
// Created by Gabriel on 4/1/2025.
//
#include <iostream>
#include "../include/Entitati.h"

#include <bits/stl_algo.h>


Entity::Entity(const double x, const double y, const Texture2D &Texture) : coordX(x), coordY(y), texture(Texture) {
    this->x = x + Texture.width;
    this->y = y + Texture.height;
}

Entity::Entity(const Texture2D &Texture) : texture(Texture) {
    this->x = x + Texture.width;
    this->y = y + Texture.height;
};

[[nodiscard]] double Entity::coord_x() const {
    return coordX;
}

[[nodiscard]] double Entity::coord_y() const {
    return coordY;
}

[[nodiscard]] double Entity::x1() const {
    return x;
}

[[nodiscard]] double Entity::y1() const {
    return y;
}

void Entity::draw() {
    DrawTexture(texture, floor(coordX), floor(coordY), WHITE);
}

void Entity::update() {
}

void Entity::colision(Entity &other) {
}
bool Entity::danger() const {return damage;};

Player::Player(const double x, const double y) : Entity(x, y, MarioTexture) {
    lastY = y;
}

Player::Player() : Entity(MarioTexture) {
}

void Player::handleInput() {
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        speed -= DefaultSpeed * ProcentAlergare;
    } else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        speed += DefaultSpeed * ProcentAlergare;
    } else {
        if (speed != 0) {
            if (speed < 0)
                speed += DefaultSpeed * ProcentAlergare, speed = min(speed, 0.0);
            else speed -= DefaultSpeed * ProcentAlergare, speed = max(speed, 0.0);
        }
    }
    isJumping = (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) & canJump;
}

void Player::moveX() {
    speed = clamp(speed, -DefaultSpeed * 1.5, DefaultSpeed * 1.5);
    coordX += speed;
}

void Player::moveY() {
    if (isJumping) {
        coordY -= Jump;
        if (coordY <= JumpMax)
            canJump = false;
    } else {
        if (coordY != lastY && cont == false)
            coordY += Jump, canJump = false;
        else if (coordY != lastY && cont == true) {
            if (coordY > JumpMin)
                coordY -= Jump;
            else cont = false;
        } else canJump = true, cont = true;
    }
}

void Player::update() {
    handleInput();
    moveX();
    moveY();
}

void Player::colision(Entity &other) {
    if (other.danger())
        health --;
}
void Player::gravity() {
    // if (canJump) {
    //     if ()
    // }
}


Enviroment::Enviroment(const double x, const double y) : Entity(x, y, BrickTexture) {
}

Enviroment::Enviroment() {
    texture = BrickTexture;
}

game* game::instance = nullptr;

game* game::GetInstance() {
    if(instance == nullptr) {
        instance = new game();
    }
    return instance;
}

void game::insert(const shared_ptr<Entity> &entity) {
    for (int i = entity->coord_y(); i <= entity->y1(); i++)
        for (int j = entity->coord_x(); j <= entity->x1(); j++) {
         //   grid[i][j].push_back(entity);
            grid[i][j] = entity;
        }
}

void game::deleteEntity(const shared_ptr<Entity> &entity) {
    for (int i = entity->coord_y(); i <= entity->y1(); i++)
        for (int j = entity->coord_x(); j <= entity->x1(); j++)
           // for (int p = 0; p < grid[i][j].size(); p++)
               // if (grid[i][j][p] == entity)
                   // grid[i][j].erase(grid[i][j].begin() + p);
                       grid[i][j] = nullptr;
}

void game::topColision(const shared_ptr<Entity> &entity, int y) const {
    for (int i = entity->coord_x(); i <= entity->x1(); i++)
        //for (int j = 0; j < grid[y][i].size(); j ++)
            entity->colision(*grid[y][i]);
}

void game::bottomColision(const shared_ptr<Entity>& entity, int y) const {
    for (int i = entity->coord_x(); i <= entity->x1(); i++)
       // for (int j = 0; j < grid[y][i].size(); j ++)
            entity->colision(*grid[y][i]);
}

void game::leftColision(const shared_ptr<Entity>& entity, int x) const {
    for (int i = entity->coord_y(); i <= entity->y1(); i++)
        //for (int j = 0; j < grid[i][x].size(); j ++)
            entity->colision(*grid[i][x]);
}

void game::rightColision(const shared_ptr<Entity> &entity, int x) const {
    for (int i = entity->coord_y(); i <= entity->y1(); i++)
            entity->colision(*grid[i][x]);
}
void game::colision(const shared_ptr<Entity> &entity) {
    // for (int i = entity->coord_y(); i <= entity->y1(); i++) {
    //     if (i == entity->coord_y() || i == entity->y1())
    //         for (int j = entity->coord_x(); j <= entity->x1(); j++) {
    //             for (int p = 0; p < grid[i][j].size(); p++)
    //                 entity->colision(*grid[i][j][p]);
    //         }
    //     else {
    //         int j = entity->coord_x();
    //         for (int p = 0; p < grid[i][j].size(); p++)
    //             entity->colision(*grid[i][j][p]);
    //         j = entity->x1();
    //         for (int p = 0; p < grid[i][j].size(); p++)
    //             entity->colision(*grid[i][j][p]);
    //     }
    // }


}

void game::setValid() {
    ///daca player.health <= 0 false
}
void game::StartGameLoop() {
    InitWindow(screenWidth, screenHeight, "Hello World");
    SetTargetFPS(60);
    ClearBackground(GREEN);
    Player player(screenWidth / 2, screenHeight / 2);
    for (int i = 0; i < screenWidth; ) {
        shared_ptr<Enviroment> a = make_shared<Enviroment>(i, screenHeight - BrickTexture.height);

        i = i + BrickTexture.width;
        entities.push_back(a);
    }
    game* Game = game::GetInstance();
    //ToggleFullscreen();
    while(!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(GREEN);
        player.update();
        player.draw();
        draw();
        EndDrawing();
    }
}
void game::draw() {
    for (int i = 0; i < entities.size(); i++) {entities[i]->draw();}
}




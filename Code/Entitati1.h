#include <cmath>
#include <../cmake-build-debug/_deps/raylib-src/src/raylib.h>
#include "include/defineuri.h"

using namespace std;
class Entity
{
protected:
    double coordX = 0, coordY = 0, x = 0, y = 0;
    int health = 1;
    double speed = 0;
    bool moving = true;
    Texture2D texture;
    static void update() {}
public:
    Entity(const double x, const double y, Texture2D Texture) : coordX(x), coordY(y), texture(Texture)
    {
        this -> x = x + Texture.width;
        this -> y = y + Texture.height;
    }
    Entity(Texture2D Texture) : texture(Texture)
    {
        this -> x = x + Texture.width;
        this -> y = y + Texture.height;
    };
    Entity() = default;
    void draw(int cameraX)
    {
        DrawTexture(texture, floor(coordX) - cameraX, floor(coordY), WHITE);
    }
};
class Player : public Entity
{
    double lastY = 0;
    bool jump = true, cont = true;
public:
    Player(const double x, const double y) : Entity(x, y, MarioTexture)
    {
        lastY = y;
    }
    Player() : Entity(MarioTexture)
    {
    }
    void update()
    {
        if (!moving)
        {
            if (speed < 0)
                speed += DefaultSpeed * ProcentAlergare, speed = min(speed, 0.0);
            else speed -= DefaultSpeed * ProcentAlergare,  speed = max(speed, 0.0);

            if (coordY != lastY && cont == false)
                coordY += Jump, jump = false;
            else if (coordY != lastY && cont == true)
            {
                if (coordY > JumpMin)
                    coordY -= Jump;
                else cont = false;
            }
            else jump = true, cont = true;

            return;
        }
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        {
            coordX += speed;
            speed -= DefaultSpeed * ProcentAlergare;
            speed = max(speed, -DefaultSpeed * 1.5);
        }
        else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        {
            coordX += speed;
            speed += DefaultSpeed * ProcentAlergare;
            speed = min(speed, DefaultSpeed * 1.5);
        }
        else
        {
            if (speed != 0)
            {
                coordX += speed;
                if (speed < 0)
                    speed += DefaultSpeed * ProcentAlergare, speed = min(speed, 0.0);
                else speed -= DefaultSpeed * ProcentAlergare,  speed = max(speed, 0.0);
            }
        }
        if ((IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) && jump)
        {
            if (coordY > JumpMax)
                coordY -= Jump;
            else jump = false;
        }
        else
        {
            if (coordY != lastY && cont == false)
                coordY += Jump, jump = false;
            else if (coordY != lastY && cont == true)
            {
                if (coordY > JumpMin)
                    coordY -= Jump;
                else cont = false;
            }
            else jump = true, cont = true;
        }

    }
};
class Brick : public Entity
{
public:
    Brick(const double x, const double y);
    Brick()
    {
        texture = BrickTexture;
    }
};
class Game {
    public:
    void draw(vector <Entity> &v);
};
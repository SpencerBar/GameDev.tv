#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getWorldPos() { return worldPos; }
    void undoMovement();
    Rectangle getCollisionRec();
    virtual void tick(float deltaTime);
    virtual Vector2 getScreenPos() = 0;
    bool getAlive() {return alive;}
    void setAlive(bool isAlive){alive = isAlive;}

protected:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    
    Vector2 worldPos{};          // used to move the world
    Vector2 worldPosLastFrame{}; // last frames world positon
    float rightLeft{1.f};        // 1 : facing right, -1 facing left
    float runningTime{};         // time between frame updates
    int frame{};                 // animation variables
    int maxFrames{6};            // max
    float updateTime{1.f / 12.f};
    float thpeed{4.f};
    float width{};
    float height{};
    float scale{6.0};
    Vector2 velocity{};
    
private:
    bool alive {true};

};
#endif
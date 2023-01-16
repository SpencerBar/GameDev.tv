#ifndef ENEMY_H
#define ENEMY_H
#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idle_tex, Texture2D run_tex);
    virtual void tick(float deltaTime) override;
    void setTarget(Character* hero) {target = hero;}
    virtual Vector2 getScreenPos() override;

private:
Character* target;
float damagePerSec{10.f};
float radius{25.f};
   
};

#endif
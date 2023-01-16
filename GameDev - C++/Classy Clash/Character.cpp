#include "Character.h"
#include "raymath.h"

Character::Character(int win_w, int win_h) : win_w(win_w),
                                             win_h(win_h)
{
    width = texture.width / maxFrames;
    height = texture.height;
}

Vector2 Character::getScreenPos()
{
    return Vector2{

        static_cast<float>(win_w) / 2.0f - scale * (0.5f * width),
        static_cast<float>(win_h) / 2.0f - scale * (0.5f * height)};
}

void Character::tick(float deltaTime)
{
    if(!getAlive()) return;

    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0; // detect if wasd are down and move in the correct direction
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0;

    BaseCharacter::tick(deltaTime);
    Vector2 origin{};
    Vector2 offset{};
    float rotation{};
    if (rightLeft > 0.f) // direction facing
    {
        origin = {0.f, weapon.height * scale}; // set weapon origin
        offset = {45.f, 85.f};                 // move weapon on character
        weaponCollisionRec = {
            getScreenPos().x + offset.x,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        }; // set collision to weapon postion
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = 35.f : rotation = 0.f; // swing weapon
    }
    else
    {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {45.f, 85.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x - weapon.width * scale,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        }; // set collision to weapon postion
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = -35.f : rotation = 0.f; //swing weapon
    }
    // draw the sword
    Rectangle source{0.f, 0.f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
    Rectangle dest{getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * scale, weapon.height * scale};
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);
}

  void Character::takeDamage(float damage)
    {
        health -= damage;
        if(health <= 0.f)
        {
            setAlive(false);
        }
    }

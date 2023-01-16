#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    const int win_d[2]{768, 786};

    InitWindow(win_d[0], win_d[1], "Classy Clash"); // set window size [width, height]

    Texture2D map = LoadTexture("nature_tileset/ccmap2424.png"); // load in map texture

    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0f};

    Character hero(win_d[0], win_d[1]); // initialize hero character class

    // array for props
    Prop props[2]{
        Prop{Vector2{850.f, 550.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{850.f, 1600.f}, LoadTexture("nature_tileset/Log.png")}};

    Enemy goblin{
        Vector2{800.f, 300.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"), // initiallize goblin enemy with textures and position
        LoadTexture("characters/goblin_run_spritesheet.png")};
    Enemy slime{
        Vector2{500.f, 700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"), // initiallize slime enemy with textures and position
        LoadTexture("characters/slime_run_spritesheet.png")};
    Enemy *enemies[]{// initialize pointer array for all enemies
                     &goblin,
                     &slime};

    for (auto enemy : enemies)
    {
        enemy->setTarget(&hero);
    };

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(hero.getWorldPos(), -1.f);  // map render
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE); // draw map with postion mapPoss

        // draw the props
        for (auto prop : props) // draw props
        {
            prop.Render(hero.getWorldPos());
        }

        if (!hero.getAlive()) // character isnt alive
        {
            DrawText("Game Over!", win_d[0] / 2.5, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else // character is ra ra rasputin (alive)
        {
            std::string heroHealth = "HP: ";
            heroHealth.append(std::to_string(hero.getHealth()), 0, 5);
            DrawText(heroHealth.c_str(), win_d[0] / 2.5, 45.f, 40, RED);
        }
        hero.tick(GetFrameTime()); // call hero tick function

        // check map bounds
        if (hero.getWorldPos().x < 0.f ||
            hero.getWorldPos().y < 0.f ||
            hero.getWorldPos().x + win_d[0] > map.width * mapScale ||
            hero.getWorldPos().y + win_d[1] > map.height * mapScale)
        {
            hero.undoMovement();
        }
        for (auto prop : props) // check prop collosion with hero
        {
            if (CheckCollisionRecs(prop.getCollisionRec(hero.getWorldPos()), hero.getCollisionRec()))
            {
                hero.undoMovement();
            }
        }

        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime()); // call enemy tiuck function
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) // check colision for enemies and weapon and set dealth or life
        {
            for (auto enemy : enemies) 
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(), hero.getWeaponCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
        }
        EndDrawing();
    }

    UnloadTexture(map);
    CloseWindow();
}
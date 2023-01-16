#include "raylib.h"
int main()
{
    // window dimensions
    int width {800};
    int height {450};
    InitWindow(width, height, "Axe Game");

    // circle coordinates
    int circle_x = (200);
    int circle_y = (200);
    int radius = 25;

    // circle edges
    int l_cirlce_x{circle_x - radius};
    int r_circle_x{circle_x + radius};
    int u_circle_y{circle_y - radius};
    int b_circle_y{circle_y + radius};
    
     //rectangle size
    int axe_w{50};
    int axe_h{50};

     // rectangle coordinates
    int axe_x{400};
    int axe_y{0};
    int direction{10};

    //rectang edges
    int l_axe_x{axe_x};
    int r_axe_x{axe_x + axe_h};
    int u_axe_y{axe_y};
    int b_axe_y{axe_y + axe_w};
    
    //Fail condition
    bool collision_with_axe = 
                        (b_axe_y >= u_circle_y) && 
                        (u_axe_y <= b_circle_y) && 
                        (l_axe_x <= r_circle_x) && 
                        (r_axe_x >= l_cirlce_x);
       
    // options
   
    int FPS{60};
    int MoveSense{10};
    SetTargetFPS(FPS);

    while (WindowShouldClose() != true)
    {
        BeginDrawing();
        ClearBackground(BLACK);

        
       
        if (collision_with_axe)
        {
            DrawText("You Died!", (width/2), (height/2), 20, RED);
        }
        else{
            // game logic begins

            // update edges
            l_cirlce_x = circle_x - radius;
            r_circle_x = circle_x + radius;
            u_circle_y = circle_y - radius;
            b_circle_y = circle_y + radius;
            l_axe_x = axe_x;
            r_axe_x = axe_x + axe_h;
            u_axe_y = axe_y;
            b_axe_y = axe_y + axe_w;

            //update collision
            collision_with_axe = 
                        (b_axe_y >= u_circle_y) && 
                        (u_axe_y <= b_circle_y) && 
                        (l_axe_x <= r_circle_x) && 
                        (r_axe_x >= l_cirlce_x);

            // draw shapes            
            DrawCircle(circle_x, circle_y, radius, WHITE);
            DrawRectangle(axe_x, axe_y, axe_w, axe_h, RED);

            // move the axe
            axe_y += direction;

            if (axe_y > height - axe_h || axe_y < 0)
            {
            direction = -direction; 
            }
            //move the circle
            if (IsKeyDown(KEY_D) && circle_x <= (width-radius))
            {
                circle_x += MoveSense;
            }
            if (IsKeyDown(KEY_A) &&circle_x >=(0+ radius))
            {
                circle_x -= MoveSense;
            }
            if (IsKeyDown(KEY_W) &&circle_y >=(0 + radius))
            {
                circle_y -= MoveSense;
            }
            if (IsKeyDown(KEY_S) &&circle_y <= (height - radius) )
            {
                circle_y += MoveSense;
            }
            //game logic ends
        }


        EndDrawing();
    }
    
} 
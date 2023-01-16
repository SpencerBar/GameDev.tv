#include "raylib.h"

struct AnimData
{
    Rectangle rec; // spirte dimensions
    Vector2 pos;  // sprite postion
    int frame; // keep trakc of current frame
    float updateTime; // how long between frame updates
    float runningTime; // how long since the last update
    int maxFrame; // how many frames in the sprite page
};

// checks if something is on the ground
bool isOnGround(AnimData data, int window_h)
{
    return data.pos.y >= window_h - data.rec.height;
}

// updates the frame of objects
AnimData updateAnimData(AnimData data, float dT)
{
    data.runningTime += dT;
    if (data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0;
        // update animation frame
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if(data.frame > data.maxFrame)
        {
            data.frame = 0;
        }
    }
    return data;
}

int main()
{
    // set window size
    int windowDimensions[2]{512,380};

    // open window and set fps
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher");

    //acceleration due to gravity (pixels/s^2) 
    const int gravity{1'000};

    //scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData{{0.0, 0.0, scarfy.width/6, scarfy.height}, // Rectangle Rec
        {windowDimensions[0]/2 - scarfyData.rec.width/2, windowDimensions[1] - scarfyData.rec.height }, // vector2 pos
        0, // int frame
        1.0/12.0, //float updateTime
        0.0, // float runningTime
        5 // int maxFrame
    };
  
    // nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    const int sizeOfnebulae{10};
    AnimData nebulae[sizeOfnebulae] {};

    for (int i{0}; i < sizeOfnebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 0.0;
        nebulae[i].pos.x = windowDimensions[0] + i * 300;
        nebulae[i].maxFrame = 7;
    }

    float finishLine{ nebulae[sizeOfnebulae - 1].pos.x };

    // jump velocity (pixel/s)
    const int jumpVel{-600};
    int velocity{0};
    int nebVel{-200}; // nebula velocity
    //is scarfy in the air? 
    bool isInAir{false};
    
    // load city textures
    Texture2D background = LoadTexture("textures/far-buildings.png");
    Texture2D foreground = LoadTexture("textures/foreground.png");
    Texture2D midground = LoadTexture("textures/back-buildings.png");
    Texture2D cityTexts[3]{background, midground, foreground};
    // set city scroll velocity
    float bgX{};
    float mgX{};
    float fgX{};
    float cityScroll[3]{bgX, mgX, fgX};

    // did scarfy hit an obstacle
    bool collision{};
    //setting targetframe rate
    SetTargetFPS(60);

    // meat of the window
    while(!WindowShouldClose())
    {
        //delta time since last frame
        float dT{GetFrameTime()};
    
        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);
        //scroll background layers
        for (int i{}; i<3; i++)
        {
            cityScroll[i] -= (20 +i*20)*dT;
            if(cityScroll[i] <= -cityTexts[i].width*2) // background
            {
                cityScroll[i] = 0.0;
            }
        }
       // print background layers
        for (int i{}; i<3; i++)
        {
        Vector2 bg1Pos{cityScroll[i], 0.0};
        DrawTextureEx(cityTexts[i], bg1Pos, 0.0, 2.0, WHITE);
        Vector2 bg2Pos{cityScroll[i] + cityTexts[i].width*2, 0.0};      // background
        DrawTextureEx(cityTexts[i], bg2Pos, 0.0, 2.0, WHITE);
        }   

        // move the finish line     
        finishLine += dT *nebVel;

        //ground check
        if(isOnGround(scarfyData, windowDimensions[1]))
        {
            //rectange on ground remove velocity
            velocity = 0;
            isInAir = false;
        }
        else
        {
            //rectange is in the air
            //apply gravity based on delta time
            velocity += dT * gravity;
            isInAir = true;

        }

        // check for jump
        if(IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            // jump velocity added            
            velocity += jumpVel;
        }
       
        //update nebulae x position
        for (int i{0}; i < sizeOfnebulae; i++)
        {
            nebulae[i].pos.x += dT *nebVel;
            
        }
          //update scarfy y position 
        scarfyData.pos.y += dT * velocity;
        //  scarfy run animation
        if(!isInAir) // stops animation in air
        {
            
            scarfyData = updateAnimData(scarfyData, dT);
            
        }

        // nebula animation iteration
        for(int i=0; i<sizeOfnebulae; i++)
            {
                nebulae[i] = updateAnimData(nebulae[i], dT);
            }
         

        
        for(AnimData nebula : nebulae)
        {
            float pad{50};
            Rectangle nebRec{
                nebula.pos.x + pad,
                nebula.pos.y + pad,
                nebula.rec.width - 2 *pad,
                nebula.rec.height - 2 * pad,
            };
            Rectangle scarfyRec{
                scarfyData.pos.x,
                scarfyData.pos.y,
                scarfyData.rec.width,
                scarfyData.rec.height,
            };
            if(CheckCollisionRecs(nebRec, scarfyRec))
            {
                collision = true;
            }
        }
        if(collision)
        {
            //lose the game
            DrawText("Game Over!", windowDimensions[0]/4, windowDimensions[1]/2, 40, BLUE);
        }
        else if (finishLine <= scarfyData.pos.x)
        {
            //win the game
            DrawText("You Win!!", windowDimensions[0]/4, windowDimensions[1]/2, 40, GREEN);
        }
        else
        {
            //draw nebula
            for (int i{0}; i < sizeOfnebulae; i++)
            {
                DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
            }

            //draw scarfy
            DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        }

      
        // end drawing
        EndDrawing();
    } 
    
    //cleanup
    UnloadTexture(midground);
    UnloadTexture(foreground);
    UnloadTexture(background);
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
    
}
#include "raylib.h"

class Prop
{
public:
    Prop(Vector2 pos, Texture2D tex);
    void Render(Vector2 heroPos);
    Rectangle getCollisionRec(Vector2 heroPos);
private:
    Texture2D texture{};
    Vector2 worldPos{};
    float scale{4.f};
    float width{};
    float hieght{};
};
#include <cmath>
#include <raylib.h>

constexpr int window_width{1920};
constexpr int window_height{1080};


int main(){
    InitWindow(window_width, window_height, "t");
    SetTargetFPS(60);
    Shader shader = LoadShader(0, "fragshader.fs");

    Image blankimg = GenImageColor(window_width, window_height, WHITE);
    Texture2D txtr = LoadTextureFromImage(blankimg);
    UnloadImage(blankimg);

    int timeLoc = GetShaderLocation(shader, "time");
    int resLoc = GetShaderLocation(shader, "iRes");
    int cameraLoc = GetShaderLocation(shader, "camerapos");
    int yawLoc = GetShaderLocation(shader, "yaw");
    int pitchLoc = GetShaderLocation(shader, "pitch");
    int lockLoc = GetShaderLocation(shader, "locked");

    float resolution[2] = {window_width,window_height};
    SetShaderValue(shader, resLoc, resolution, SHADER_UNIFORM_VEC2);

    Vector3 camerapos{0,0,-3};
    float x_speed{0.2};
    float z_speed{0.2};
    float yaw = 0.0f;   
    float pitch = 0.0f; 
    int locked={0}; //0=locked, 1=unlocked

    DisableCursor();
    while(!WindowShouldClose()){

        float time = GetTime();
        float dt = GetFrameTime();

        Vector2 mouseDelta = GetMouseDelta();
        float sensitivity = 0.003f;
        yaw += mouseDelta.x * sensitivity;
        pitch -= mouseDelta.y * sensitivity;
        if (pitch > 1.55f) pitch = 1.55f;
        if (pitch < -1.55f) pitch = -1.55f;
        float speed = 1.5f * dt;

        Vector3 forward = { sinf(yaw), 0.0f, cosf(yaw) };
        Vector3 right = { cosf(yaw), 0.0f, -sinf(yaw) };

        if(IsKeyDown(KEY_W)) { camerapos.x += forward.x * speed; camerapos.z += forward.z * speed; }
        if(IsKeyDown(KEY_S)) { camerapos.x -= forward.x * speed; camerapos.z -= forward.z * speed; }
        if(IsKeyDown(KEY_D)) { camerapos.x += right.x * speed; camerapos.z += right.z * speed; }
        if(IsKeyDown(KEY_A)) { camerapos.x -= right.x * speed; camerapos.z -= right.z * speed; }
        if(IsKeyDown(KEY_SPACE)) { camerapos.y += speed; } 
        if(IsKeyDown(KEY_LEFT_SHIFT)) { camerapos.y -= speed; }
        if(IsKeyPressed(KEY_L))locked = 1 - locked;

        SetShaderValue(shader, lockLoc, &locked, SHADER_UNIFORM_INT);
        SetShaderValue(shader, timeLoc, &time, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, cameraLoc, &camerapos, SHADER_UNIFORM_VEC3);
        SetShaderValue(shader, yawLoc, &yaw, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, pitchLoc, &pitch, SHADER_UNIFORM_FLOAT);

        BeginDrawing();
        ClearBackground(WHITE);
       
        BeginShaderMode(shader);
        DrawTexture(txtr, 0, 0, WHITE);
        EndShaderMode();
        
        EndDrawing();

    }
    UnloadTexture(txtr);
    UnloadShader(shader);
    CloseWindow();
    return 0;

}

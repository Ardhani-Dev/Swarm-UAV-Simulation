#include <iostream>
#include <raylib.h>

int main () { 
    InitWindow(800, 600, "Swarm UAV Main");
    SetTargetFPS(60); 

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 12.0f, 12.0f, 12.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    while (!WindowShouldClose()){
        UpdateCamera(&camera, CAMERA_ORBITAL);

        BeginMode3D(camera);
            DrawGrid(100, 1.0f); //Grid 100 x 100 Jarak antar grid 1.0
        BeginDrawing();
            ClearBackground((Color){ 10, 10, 15, 255 }); // Void Background

            BeginMode3D(camera);
                DrawGrid(100, 1.0f); //Grid 100 x 100 Jarak antar grid 1.0

        EndDrawing();
        EndMode3D();
    }   
    CloseWindow();
    return 0;
}


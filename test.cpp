#include "raylib.h"

// 1. Membuat Blueprint untuk objek Drone
struct Drone {
    Vector3 position;
    Vector3 velocity;
    Color color;
};

int main() {
    InitWindow(800, 600, "Swarm UAV SAR - Simulasi Bergerak");
    SetTargetFPS(60);

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 12.0f, 12.0f, 12.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // 2. Melahirkan 1 unit drone dengan posisi dan kecepatan awal
    Drone uav = {
        { 0.0f, 1.0f, 0.0f },     // Posisi awal (x, y, z)
        { 0.08f, 0.0f, 0.05f },   // Kecepatan (melaju ke arah X dan Z)
        RED                       // Warna drone
    };

        Drone uav1 = {
        { 2.0f, 1.0f, 5.0f },     // Posisi awal (x, y, z)
        { 0.08f, 0.0f, 0.05f },   // Kecepatan (melaju ke arah X dan Z)
        GREEN                       // Warna drone
    };


    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_ORBITAL);

        // --- UPDATE LOGIC (Matematika Pergerakan) ---
        // Drone bergerak maju sesuai kecepatannya
        uav.position.x += uav.velocity.x;
        uav.position.z += uav.velocity.z;
        uav1.position.x += uav1.velocity.x;
        uav1.position.z += uav1.velocity.z;

        // Logika pantulan sederhana agar drone tidak terbang hilang ke luar grid
        if (uav.position.x > 5.0f || uav.position.x < -5.0f) uav.velocity.x *= -1.0f;
        if (uav.position.z > 5.0f || uav.position.z < -5.0f) uav.velocity.z *= -1.0f;
        if (uav1.position.x > 5.0f || uav1.position.x < -5.0f) uav1.velocity.x *= -1.0f;
        if (uav1.position.z > 5.0f || uav1.position.z < -5.0f) uav1.velocity.z *= -1.0f;

        // --- DRAW LOGIC (Visualisasi 3D) ---
        BeginDrawing();
            ClearBackground((Color){ 10, 10, 15, 255 }); // Void Background

            BeginMode3D(camera);
                DrawGrid(10, 1.0f); // Grid dasar ukuran 10x10

                // Gambar fisik drone (Kubus)
                DrawCube(uav.position, 0.6f, 0.6f, 0.6f, uav.color);
                DrawCubeWires(uav.position, 0.6f, 0.6f, 0.6f, WHITE);
                DrawCube(uav1.position, 0.6f, 0.6f, 0.6f, uav1.color);
                DrawCubeWires(uav1.position, 0.6f, 0.6f, 0.6f, BLACK);

                // Gambar garis vektor berwarna hijau ke arah depan drone (menunjukkan arah gerak)
                Vector3 arahDepan = { 
                    uav.position.x + (uav.velocity.x * 15), 
                    uav.position.y, 
                    uav.position.z + (uav.velocity.z * 15) 
                };
                DrawLine3D(uav.position, arahDepan, GREEN);

                  Vector3 arahDepan1 = { 
                    uav1.position.x + (uav1.velocity.x * 15), 
                    uav1.position.y, 
                    uav1.position.z + (uav1.velocity.z * 15) 
                };
                DrawLine3D(uav1.position, arahDepan1, RED);

            EndMode3D();

            DrawText("Tes Simulasi Raylib", 10, 10, 18, RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
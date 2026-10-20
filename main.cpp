#include "raylib.h"

int main() {
    // 1. Inisialisasi Ukuran Jendela Simulasi
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Swarm UAV SAR - 3D Void Test");

    // 2. Setup Kamera 3D
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Posisi sudut pandang
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Titik tengah yang dilihat
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Arah atas dunia 3D
    camera.fovy = 45.0f;                                // Field of View (FOV)
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);

    // 3. Game Loop Utama
    while (!WindowShouldClose()) {
        // Kontrol kamera: Tahan Klik Kiri + Drag Mouse untuk memutar kamera 3D
        UpdateCamera(&camera, CAMERA_ORBITAL);

        // 4. Render Visual
        BeginDrawing();
            // Latar belakang void serba gelap (R:10, G:10, B:15)
            ClearBackground((Color){ 10, 10, 15, 255 });

            BeginMode3D(camera);
                // Grid tipis sebagai acuan bidang dasar
                DrawGrid(20, 1.0f);

                // Representasi sementara 1 unit drone (kubus merah + garis putih)
                DrawCube((Vector3){ 0.0f, 1.0f, 0.0f }, 1.0f, 1.0f, 1.0f, RED);
                DrawCubeWires((Vector3){ 0.0f, 1.0f, 0.0f }, 1.0f, 1.0f, 1.0f, WHITE);
            EndMode3D();

            // Teks penanda di pojok kiri atas
            DrawText("3D VOID TEST - Drag Mouse untuk Putar Kamera", 10, 10, 16, RAYWHITE);
        EndDrawing();
    }

    // 5. Bersihkan Memori & Tutup Jendela
    CloseWindow();
    return 0;
}
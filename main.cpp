#include "raylib.h"
#include <cstdlib>
#include <ctime>

int main() {
    InitWindow(1000, 700, "Swarm UAV SAR - Procedural Biome Terrain");
    SetTargetFPS(60);

    // Mengambil waktu dari jam sistem komputermu sebagai bibit acak 
    // agar rand() selalu menghasilkan angka unik setiap kali aplikasi dibuka
    srand(time(NULL)); 

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 35.0f, 25.0f, 35.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // --- TERRAIN & BIOME GENERATION SCOPE ---
    // 1. Membangkitkan peta ketinggian Perlin Noise acak
    int offsetX = rand() % 10000;
    int offsetY = rand() % 10000;
    Image petaKetinggian = GenImagePerlinNoise(100, 100, offsetX, offsetY, 2.0f);

    // 2. Membangkitkan gambar baru yang akan diwarnai sebagai Biome
    Image petaBiome = GenImageColor(100, 100, BLANK);

    // 3. Melakukan pemindaian piksel untuk menentukan warna Biome berdasarkan ketinggian
    for (int y = 0; y < 100; y++) {
        for (int x = 0; x < 100; x++) {
            // Mengambil warna dari peta ketinggian asli (grayscale)
            Color warnaAsli = GetImageColor(petaKetinggian, x, y);
            float ketinggian = warnaAsli.r; // Rentang nilai kecerahan 0 (hitam) sampai 255 (putih)
            
            Color warnaBiome;
            // Menentukan bioma berdasarkan elevasi (ketinggian)
            if (ketinggian < 80) warnaBiome = DARKBLUE;        // Lembah Terdalam / Air
            else if (ketinggian < 100) warnaBiome = BLUE;      // Air Dangkal
            else if (ketinggian < 110) warnaBiome = YELLOW;    // Pantai / Dataran Pasir
            else if (ketinggian < 170) warnaBiome = DARKGREEN; // Hutan / Daratan Utama
            else if (ketinggian < 210) warnaBiome = DARKBROWN; // Pegunungan Batu
            else warnaBiome = RAYWHITE;                        // Puncak Salju
            
            // Mewarnai piksel pada peta Biome
            ImageDrawPixel(&petaBiome, x, y, warnaBiome);
        }
    }
    
    // 4. Mengubah gambar Biome menjadi tekstur yang bisa dipasang ke model 3D
    Texture2D teksturTerrain = LoadTextureFromImage(petaBiome);
    
    // 5. Mengubah gambar hitam-putih menjadi jaring 3D sesungguhnya (Mesh)
    // Ketinggian puncak maksimal diatur ke 12.0f
    Mesh jaringGunung = GenMeshHeightmap(petaKetinggian, (Vector3){ 40.0f, 12.0f, 40.0f });
    Model terrain = LoadModelFromMesh(jaringGunung);
    
    // 6. Memasang tekstur Biome ke atas model 3D terrain
    terrain.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = teksturTerrain;

    // Menghapus gambar dari memori CPU karena sudah dipindahkan ke memori GPU (VRAM)
    UnloadImage(petaKetinggian);
    UnloadImage(petaBiome);
    // ------------------------------------------

    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_ORBITAL);

        BeginDrawing();
            ClearBackground((Color){ 10, 10, 15, 255 });

            BeginMode3D(camera);
                DrawGrid (100, 0.5f); // Grid dasar ukuran 1000x1000
                // Menggambar model terrain dan menggesernya agar berada persis di tengah sumbu
                DrawModel(terrain, (Vector3){ -20.0f, 0.0f, -20.0f }, 1.0f, WHITE);
            EndMode3D();

            DrawText("Procedural Biome Terrain Aktif | Drone dinonaktifkan sementara", 10, 10, 18, RAYWHITE);
        EndDrawing();
    }

    // Pembersihan memori GPU
    UnloadTexture(teksturTerrain);
    UnloadModel(terrain);
    CloseWindow();
    return 0;
}
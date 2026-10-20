#include <iostream>

int main() {
    // Data posisi dan kecepatan awal
    float posX = 10.0f;
    float posY = 20.0f;
    float velX = 2.5f;
    float velY = 1.5f;

    std::cout << "=== TES SIMULASI C++ ===" << std::endl;
    std::cout << "Posisi Awal  : (" << posX << ", " << posY << ")" << std::endl;

    // Simulasi pembaruan posisi (perhitungan 1 detik/frame)
    posX += velX;
    posY += velY;

    std::cout << "Posisi Baru  : (" << posX << ", " << posY << ")" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Status: Compiler & terminal berjalan sempurna!" << std::endl;

    return 0;
}
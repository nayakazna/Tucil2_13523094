#pragma once

#include <iostream>
#include <cstdint>
#include <stdexcept>
#include <vector>
#include <chrono>
#include <algorithm>
#include <string>
#include <memory>

#include "err_measure.hpp"
#include "quadtree.hpp"
#include "imgio.hpp"

namespace algo {
    static int metode;          // metode pengukuran galat
    static int minimumBlok;     // ukuran minimum blok
    static float ambang;        // ambang batas galat

    struct hasilData {
        std::chrono::milliseconds waktuEksekusi;
        int jumlahNode;
        int kedalaman;
    };

    void warnaiBlok(imgio::Gambar& gambar, int x, int y, int width, int height, uint8_t r, uint8_t g, uint8_t b) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                int index = ((y + i) * gambar.width + (x + j)) * 3;
                gambar.data[index] = r;
                gambar.data[index + 1] = g;
                gambar.data[index + 2] = b;
            }
        }
    }

    quadtree::QuadtreeNode* kompresiQuadtree(imgio::Gambar& gambar, int x, int y, int width, int height, int imageWidth) {
        // Menghitung galat untuk blok saat ini
        float galat = err_measure::calculateGalat(&gambar.data, x, y, width, height, imageWidth, metode);

        // Jika galat lebih besar dari ambang batas, bagi blok menjadi 4 bagian
        if (galat > ambang && width > minimumBlok && height > minimumBlok) {
            int halfWidth = width / 2;
            int halfHeight = height / 2;

            quadtree::QuadtreeNode* node = new quadtree::QuadtreeNode(x, y, width, height);
            node->setAnak(0, kompresiQuadtree(gambar, x, y, halfWidth, halfHeight, imageWidth));
            node->setAnak(1, kompresiQuadtree(gambar, x + halfWidth, y, width-halfWidth, halfHeight, imageWidth));
            node->setAnak(2, kompresiQuadtree(gambar, x, y + halfHeight, halfWidth, height-halfHeight, imageWidth));
            node->setAnak(3, kompresiQuadtree(gambar, x + halfWidth, y + halfHeight, width-halfWidth, height-halfHeight, imageWidth));
            return node;
        } else {
            // Jika galat lebih kecil atau sama dengan ambang batas,
            // buat node daun dengan warna rata-rata blok
            err_measure::Warna warna = err_measure::calculateRerataWarna(&gambar.data, x, y, width, height, imageWidth);
            warnaiBlok(gambar, x, y, width, height, warna.r, warna.g, warna.b);
            // Buat node daun
            return new quadtree::QuadtreeNode(x, y, width, height, true);
        }

    }

    hasilData mainAlgo(imgio::Gambar& gambar, int imageWidth) {
        // Meminta input dari pengguna untuk metode galat
        galat:
        std::cout << "Pilih metode galat:\n";
        std::cout << "1. Variansi\n";
        std::cout << "2. MAD (Mean Absolute Deviation)\n";
        std::cout << "3. MPD (Maximum Pixel Difference)\n";
        std::cout << "4. Entropi\n";
        std::cout << "Masukkan pilihan (1-4): ";
        std::cin >> metode;
        if (metode < 1 || metode > 4) {
            std::cerr << "\033[31mPilihan tidak valid!\033[0m" << std::endl;
            goto galat;
        }

        // Meminta input dari pengguna untuk ukuran blok
        mini:
        std::cout << "Masukkan ukuran minimum blok (misal 8, 16, 32): ";
        std::cin >> minimumBlok;
        if (minimumBlok <= 0 || minimumBlok > gambar.width || minimumBlok > gambar.height) {
            std::cerr << "\033[31mUkuran blok tidak valid!\033[0m" << std::endl;
            goto mini;
        }

        // Meminta input dari pengguna untuk ambang batas galat
        ambang:
        std::cout << "Masukkan ambang batas galat (misal 0.1, 0.2): ";
        std::cin >> ambang;
        if (ambang < 0.0f) {
            std::cerr << "\033[31mAmbang batas galat tidak valid!\033[0m" << std::endl;
            goto ambang;
        }

        hasilData hasil;

        auto start = std::chrono::high_resolution_clock::now();
        quadtree::QuadtreeNode* root = kompresiQuadtree(gambar, 0, 0, gambar.width, gambar.height, imageWidth);
        auto end = std::chrono::high_resolution_clock::now();

        hasil.waktuEksekusi = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        hasil.jumlahNode = root->hitungNode();
        hasil.kedalaman = root->hitungKedalaman();
        return hasil;
    }
} // namespace algo
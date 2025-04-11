#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <iostream>
#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "external/stb_image_write.h"    

namespace imgio {
    using namespace std;

    /// Struktur untuk menyimpan informasi gambar
    struct Gambar {
        int width;
        int height;
        int channels;
        std::vector<uint8_t> data;
    };

    // Mengecek apakah path yang diberikan adalah path absolut
    // return true jika path adalah path absolut, false jika tidak
    bool isAbsolutePath(const std::string& path) {
    return (!path.empty() && path[0] == '/') || // untuk Unix
           (path.size() > 2 && std::isalpha(path[0]) && // untuk Windows
            path[1] == ':' && (path[2] == '\\' || path[2] == '/'));
}


    /// Membaca gambar dari file ke dalam struktur Gambar
    /// return false jika gagal membaca gambar, true jika berhasil
    bool readGambar(Gambar* gambar) {
        try {
            string filename;

            cout << "Masukkan \033[1mpath absolut\033[0m menuju file gambar yang akan dimuat: ";
            std::getline(std::cin >> std::ws, filename);
            
            if (!isAbsolutePath(filename)) {
                throw runtime_error("\033[31mPath yang diberikan bukan path absolut!\033[0m");
            }

            cout << "Membaca gambar dari: " << filename << endl;
            uint8_t* data = stbi_load(filename.c_str(), &gambar->width, &gambar->height, &gambar->channels, 3);

            if (!data) {
                gambar->height = gambar->width = gambar->channels = 0;
                throw runtime_error("\033[31mGagal membaca gambar!\033[0m Pastikan file gambar ada dan formatnya didukung.");
            }

            cout << "\033[32mGambar berhasil dibaca!\033[0m \n";
            
            gambar->channels = 3;
            gambar->data.resize(gambar->width * gambar->height * gambar->channels);
            gambar->data.assign(data, data + (gambar->width * gambar->height * gambar->channels));
            stbi_image_free(data);
            return true;
        }
        catch(const exception& e) {
            cerr << e.what() << '\n';
            return false;
        }
    }

    // Menyimpan gambar ke file
    // return true jika berhasil menyimpan gambar, false jika gagal
    bool writeGambar(const Gambar& image) {
        try {
            string filename;
            cout << "Masukkan \033[1mpath absolut\033[0m (termasuk nama file gambar) untuk nyimpan hasil kompresi: ";
            std::getline(std::cin >> std::ws, filename);
            
            if (!isAbsolutePath(filename)) {
                throw runtime_error("\033[31mPath yang diberikan bukan path absolut!\033[0m");
            }
            
            cout << "Menyimpan gambar ke: " << filename << endl;
            
            if (!stbi_write_png(filename.c_str(), image.width, image.height, image.channels, image.data.data(), image.width * image.channels)) {
                throw runtime_error("\033[31mGagal menyimpan gambar!\033[0m Pastikan direktori yang dituju beneran ada.");
            }
            
            cout << "\033[32mGambar berhasil disimpan!\033[0m \n";
            return true;
        }
        catch(const exception& e) {
            cerr << e.what() << '\n';
            return false;
        }
    }

 
} // namespace imgio

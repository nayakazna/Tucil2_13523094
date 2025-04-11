#pragma once

#include <iostream>
#include <vector>
#include <cstdint>

namespace err_measure {
    struct Warna {
        float r;
        float g;
        float b;
    };

    Warna calculateRerataWarna(const std::vector<uint8_t>* warnaBlok, int x, int y, int width, int height, int imageWidth) {
        Warna rerata = {0, 0, 0};
        
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                int index = ((y + i) * imageWidth + (x + j)) * 3;
                rerata.r += warnaBlok->at(index);
                rerata.g += warnaBlok->at(index + 1);
                rerata.b += warnaBlok->at(index + 2);
            }
        }

        rerata.r /= (width * height);
        rerata.g /= (width * height);
        rerata.b /= (width * height);
        return rerata;
    }

    float variansi(const std::vector<uint8_t>* warnaBlok, int x, int y, int width, int height, int imageWidth) {
        Warna rerata = calculateRerataWarna(warnaBlok, x, y, width, height, imageWidth);

        float galat = 0.0f;
        float var_r = 0.0f;
        float var_g = 0.0f;
        float var_b = 0.0f;

        
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                int index = ((y + i) * width + (x + j)) * 3;
                var_r += (warnaBlok->at(index) - rerata.r) * (warnaBlok->at(index) - rerata.r);
                var_g += (warnaBlok->at(index + 1) - rerata.g) * (warnaBlok->at(index + 1) - rerata.g);
                var_b += (warnaBlok->at(index + 2) - rerata.b) * (warnaBlok->at(index + 2) - rerata.b);
            }
        }

        var_r /= (width * height);
        var_g /= (width * height);
        var_b /= (width * height);

        galat = (var_r + var_g + var_b) / 3.0f;
        return galat;
    }

    float MAD(const std::vector<uint8_t>* warnaBlok, int x, int y, int width, int height, int imageWidth) {
        Warna rerata = calculateRerataWarna(warnaBlok, x, y, width, height, imageWidth);

        float galat = 0.0f;
        float mad_r = 0.0f;
        float mad_g = 0.0f;
        float mad_b = 0.0f;

        
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                int index = ((y + i) * width + (x + j)) * 3;
                mad_r += std::abs(warnaBlok->at(index) - rerata.r);
                mad_g += std::abs(warnaBlok->at(index + 1) - rerata.g);
                mad_b += std::abs(warnaBlok->at(index + 2) - rerata.b);
            }
        }

        mad_r /= (width * height);
        mad_g /= (width * height);
        mad_b /= (width * height);

        galat = (mad_r + mad_g + mad_b) / 3.0f;

        return galat;
    }

    float MPD(const std::vector<uint8_t>* warnaBlok, int x, int y, int width, int height, int imageWidth) {
        Warna rerata = calculateRerataWarna(warnaBlok, x, y, width, height, imageWidth);

        float galat = 0.0f;
        float mpd_r = 0.0f;
        float mpd_g = 0.0f;
        float mpd_b = 0.0f;

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                int index = ((y + i) * width + (x + j)) * 3;
                mpd_r = std::max(mpd_r, static_cast<float>(std::abs(warnaBlok->at(index) - rerata.r)));
                mpd_g = std::max(mpd_g, static_cast<float>(std::abs(warnaBlok->at(index + 1) - rerata.g)));
                mpd_b = std::max(mpd_b, static_cast<float>(std::abs(warnaBlok->at(index + 2) - rerata.b)));
            }
        }

        galat = std::sqrt((mpd_r + mpd_g + mpd_b) / 3.0f);

        return galat;
    }

    float entropi(const std::vector<uint8_t>* warnaBlok, int x, int y, int width, int height, int imageWidth) {
        float galat = 0.0f;
        float h_r = 0.0f;
        float h_g = 0.0f;
        float h_b = 0.0f;

        // Hitung histogram untuk setiap channel warna
        int histogram_r[256] = {0};
        int histogram_g[256] = {0};
        int histogram_b[256] = {0};
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                int index = ((y + i) * width + (x + j)) * 3;
                histogram_r[warnaBlok->at(index)]++;
                histogram_g[warnaBlok->at(index + 1)]++;
                histogram_b[warnaBlok->at(index + 2)]++;
            }
        }

        // Hitung entropi untuk setiap channel warna
        for (int i = 0; i < 256; ++i) {
            if (histogram_r[i] > 0) {
                float p = static_cast<float>(histogram_r[i]) / (width * height);
                h_r -= p * std::log2(p);
            }
            if (histogram_g[i] > 0) {
                float p = static_cast<float>(histogram_g[i]) / (width * height);
                h_g -= p * std::log2(p);
            }
            if (histogram_b[i] > 0) {
                float p = static_cast<float>(histogram_b[i]) / (width * height);
                h_b -= p * std::log2(p);
            }
        }

        // Hitung galat sebagai rata-rata entropi dari ketiga channel
        galat = (h_r + h_g + h_b) / 3.0f;
        
        return galat;
    }

    float calculateGalat(const std::vector<uint8_t>* warnaBlok, int x, int y, int width, int height, int imageWidth, int metode) {
        float galat;
        
        switch (metode) {
        case 1: // variansi
            galat = variansi(warnaBlok, x, y, width, height, imageWidth);
            break;
        
        case 2: // MAD
            galat = MAD(warnaBlok, x, y, width, height, imageWidth);
            break;

        case 3: // MPD
            galat = MPD(warnaBlok, x, y, width, height, imageWidth);
            break;

        case 4: // entropi
            galat = entropi(warnaBlok, x, y, width, height, imageWidth);
            break;

        default:
            std::cerr << "\033[31mMetode galat tidak dikenali!\033[0m" << std::endl;
            return -1.0f;
            break;
        }
        return galat;
    }

} // namespace err_measure

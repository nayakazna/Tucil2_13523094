#ifndef IO_HPP
#define IO_HPP

#include <string>
#include <vector>
#include <cstdint>

namespace imgio {
    struct Gambar {
        int width;
        int height;
        int channels;
        std::vector<uint8_t> data;
    };

    bool readGambar(Gambar* gambar);
    bool writeGambar(const Gambar& image);
}

#endif

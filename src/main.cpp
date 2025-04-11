#include "modules/imgio.hpp"
#include "modules/algo.hpp"

int main() {
    std::string oriPath;
    imgio::Gambar gambar;
    if (!imgio::readGambar(&gambar, &oriPath)) return 0;
    algo::hasilData hasil = algo::mainAlgo(gambar, gambar.width);
    while (!imgio::writeGambar(gambar, hasil.waktuEksekusi, oriPath, hasil.kedalaman, hasil.jumlahNode)) {}
    return 0;
}
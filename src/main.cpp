#include "modules/imgio.hpp"
#include "modules/algo.hpp"

int main() {
    imgio::Gambar gambar;
    if (!imgio::readGambar(&gambar)) goto ret;
    algo::mainAlgo(gambar, gambar.width);
    while (!imgio::writeGambar(gambar)) {}
    ret: return 0;
}
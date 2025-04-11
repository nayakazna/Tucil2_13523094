#include "modules/imgio.hpp"
#include "modules/algo.hpp"

int main() {
    imgio::Gambar gambar;
    if (!imgio::readGambar(&gambar)) goto ret;
    algo::mainAlgo(gambar);
    while (!imgio::writeGambar(gambar)) {}
    ret: return 0;
}
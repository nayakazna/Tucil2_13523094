#include "modules/imgio.hpp"
// #include "modules/quadtree.hpp"

#include <iostream>
#include <stdexcept>
#include <memory>
#include <algorithm>
#include <cstdlib>


using namespace std;
using namespace imgio;
// using namespace quadtree;

int main() {
    Gambar gambar;
    string filename;

    if (!readGambar(&gambar)) goto ret;
    while (!writeGambar(gambar)) {}
    
    ret:
    return 0;
}
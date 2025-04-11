#pragma once

#include <memory>
#include <cstdint>
#include <stdexcept>


namespace quadtree {
    class QuadtreeNode {
        public:
            // ctor
            QuadtreeNode(int x_, int y_, int lebar_, int tinggi_, bool isDaun_, uint32_t warna_) 
                : x(x_), y(y_), lebar(lebar_), tinggi(tinggi_), isDaun(isDaun_), warna(warna_) {
                for (int i = 0; i < 4; ++i) {
                    anak[i] = nullptr;
                }
            }

            // cctor
            QuadtreeNode(const QuadtreeNode& other) 
                : x(other.x), y(other.y), lebar(other.lebar), tinggi(other.tinggi), isDaun(other.isDaun), warna(other.warna) {
                for (int i = 0; i < 4; ++i) {
                    if (other.anak[i]) {
                        anak[i] = std::make_unique<QuadtreeNode>(*other.anak[i]);
                    } else {
                        anak[i] = nullptr;
                    }
                }
            }

            // dtor
            ~QuadtreeNode() {}

            // operator=
            QuadtreeNode& operator=(const QuadtreeNode& other) {
                if (this != &other) {
                    x = other.x;
                    y = other.y;
                    lebar = other.lebar;
                    tinggi = other.tinggi;
                    isDaun = other.isDaun;
                    warna = other.warna;
                    for (int i = 0; i < 4; ++i) {
                        if (other.anak[i]) {
                            anak[i] = std::make_unique<QuadtreeNode>(*other.anak[i]);
                        } else {
                            anak[i] = nullptr;
                        }
                    }
                }
                return *this;
            }

            // getters
            int getX() const { return x; }
            int getY() const { return y; }
            int getLebar() const { return lebar; }
            int getTinggi() const { return tinggi; }
            bool getIsDaun() const { return isDaun; }
            uint32_t getWarna() const { return warna; }
            QuadtreeNode* getAnak(int i) const { return anak[i].get(); }

            // setters
            void setX(int x) { this->x = x; }
            void setY(int y) { this->y = y; }
            void setLebar(int lebar) { this->lebar = lebar; }
            void setTinggi(int tinggi) { this->tinggi = tinggi; }
            void setIsDaun(bool isDaun) { this->isDaun = isDaun; }
            void setWarna(uint32_t warna) { this->warna = warna; }
            void setAnak(int i, QuadtreeNode* node) { this->anak[i] = std::unique_ptr<QuadtreeNode>(node); }

            // method untuk menambahkan anak
            void addAnak(int i, int x_, int y_, int lebar_, int tinggi_, bool isDaun_, uint32_t warna_) {
                if (i < 0 || i >= 4) {
                    throw std::out_of_range("Index anak harus antara 0 dan 3");
                }
                anak[i] = std::make_unique<QuadtreeNode>(x_, y_, lebar_, tinggi_, isDaun_, warna_);
            }

            // method untuk menghapus anak
            void removeAnak(int i) {
                if (i < 0 || i >= 4) {
                    throw std::out_of_range("Index anak harus antara 0 dan 3");
                }
                anak[i].reset();
            }

            // method untuk mengecek apakah node memiliki anak
            bool hasChildren() const {
                for (int i = 0; i < 4; ++i) {
                    if (anak[i]) {
                        return true;
                    }
                }
                return false;
            }

        private:
            int x, y, lebar, tinggi;
            bool isDaun;
            uint32_t warna;
            std::unique_ptr<QuadtreeNode> anak[4];
    };

} // namespace quadtree


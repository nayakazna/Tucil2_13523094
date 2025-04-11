# Tucil2_13523094
Sebuah program sederhana untuk menerapkan kompresi gambar dengan Quadtree berdasarkan algoritma Divide and Conquer yang diimplementasikan dalam bahasa C++.

# Prasyarat
- Sistem operasi berbasis Windows atau Unix
- Dibutuhkan kompilator C++17 atau yang lebih baru

# Kompilasi
Salin repositori ini dengan perintah
```bash
git clone https://github.com/nayakazna/Tucil2_13523094.git
```

Pergi ke direktori utama repositori lalu kompilasikan kode sumber dengan menjalankan perintah
```bash
g++ -o bin/main src/main.cpp
```
lalu jalankan `main` atau `main.exe`
```
./bin/main         # Linux/macOS
./bin/main.exe     # Windows
```

# Penggunaan
File `main` sudah disediakan sehingga bisa langsung dijalankan tanpa kompilasi ulang

Alur program:
- Masukkan path absolut gambar sumber (contoh: E:/Gambar/input.png)
- Pilih metode perhitungan error. Program akan menampilkan daftar metode, lalu Anda cukup memasukkan angka sesuai pilihan.
- Masukkan nilai ambang batas (threshold). Nilai ini menentukan sensitivitas perbedaan warna antar blok. Nilai yang terlalu kecil bisa menyebabkan hasil tidak terlalu terkompres.
- Masukkan ukuran blok minimum. Menentukan batas terkecil pembagian blok Quadtree. Contoh: 4
- Masukkan path absolut untuk menyimpan gambar hasil. Contoh: E:/Gambar/output.png

# Author
13523094
Z. Nayaka Athadiansyah

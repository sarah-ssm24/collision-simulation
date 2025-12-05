# Laporan Collision Simulation - Sarah Shafira Maulida 5024241035
Simulasi tabrakan antara banyak lingkaran bergerak menggunakan dua algoritma:
1. **Brute Force**
2. **Quadtree**

---
## Pendahuluan
Proyek ini merupakan simulasi tabrakan antara banyak lingkaran bergerak untuk membandingkan dua metode pendeteksian tabrakan, yaitu Brute Force dan Quadtree. Melalui visualisasi real-time, pengguna dapat melihat perbedaan jumlah pengecekan yang dilakukan oleh kedua algoritma, sehingga memberikan gambaran tentang pentingnya optimasi dalam sistem dengan jumlah objek besar. Simulasi ini bertujuan untuk menunjukkan bagaimana pembagian ruang dapat meningkatkan efisiensi dibandingkan pengecekan langsung pada semua pasangan objek.

---
## Fitur
### Simulasi Banyak Objek (800 Lingkaran)
Program menampilkan ratusan lingkaran yang bergerak secara acak dan saling berinteraksi. Setiap lingkaran memiliki posisi, kecepatan, dan radius yang sama.

### Dua Metode Deteksi Tabrakan
1. **Brute Force**: Mengecek semua pasangan objek, cocok untuk pembelajaran dasar tetapi tidak efisien pada jumlah objek besar.
- Mengecek semua pasangan objek secara langsung.  
- Kompleksitas: **O(n²)**  
- Sangat berat untuk jumlah objek yang besar.
  <img width="718" height="554" alt="image" src="https://github.com/user-attachments/assets/11ae99ab-faae-40b9-9753-be67eab6d1ab" />

2. **Grid-Based Quadtree**: Membagi layar menjadi beberapa sel untuk mengurangi jumlah pengecekan, sehingga jauh lebih cepat dan efisien.
- Ruang permainan dibagi menjadi sel berukuran **120 × 120 px**.  
- Objek hanya dicek dengan objek lain yang berada di **sel yang sama**.  
- Secara signifikan mengurangi jumlah pengecekan collision.
  <img width="489" height="805" alt="image" src="https://github.com/user-attachments/assets/0abe9b21-01e9-4a6b-89a1-5234d3dda46d" />

### Visualisasi Real-Time<br>
  Setiap lingkaran digambar ulang tiap frame sehingga pengguna dapat melihat animasi pergerakan sekaligus efek tabrakannya secara langsung.
### Perbandingan Jumlah Pengecekan<br>
  Program menampilkan berapa banyak collision check yang dilakukan oleh algoritma yang sedang aktif, sehingga perbedaan performa langsung terlihat.
### Pergantian Mode dengan Tombol<br>
  Pengguna dapat menekan SPACE untuk berpindah antara mode Brute Force dan Grid-Based kapan saja selama simulasi berjalan.

## Kesimpulan
Simulasi ini memperlihatkan perbedaan signifikan antara metode Brute Force dan Quadtree dalam pendeteksian tabrakan. Walaupun brute force sederhana dan mudah dipahami, metode tersebut menjadi tidak efisien saat jumlah objek semakin besar. Sebaliknya, pendekatan Quadtree mampu mengurangi jumlah pemeriksaan tabrakan secara drastis dengan memanfaatkan pembagian ruang, sehingga menghasilkan performa yang jauh lebih baik. Melalui visualisasi real-time, pengguna dapat melihat langsung bagaimana optimasi algoritma dapat memberikan peningkatan efisiensi yang nyata dalam sistem berbasis simulasi dan fisika komputasi.

Collision Simulation: Brute Force vs Quadtree

⮞ Deskripsi Proyek : Proyek ini merupakan simulasi collision detection dua dimensi menggunakan bahasa pemrograman C++ dan library SFML. Simulasi memodelkan partikel berbentuk bubble yang bergerak secara dinamis di dalam sebuah area tertutup, saling bertabrakan, serta memantul pada batas dinding. Proyek ini bertujuan untuk memvisualisasikan dan membandingkan dua pendekatan algoritma deteksi tabrakan, yaitu Brute Force dan Quadtree, dalam konteks Computer Graphics dan simulasi fisika sederhana.

⮞ Tujuan : Tujuan dari proyek ini adalah untuk mengimplementasikan sistem collision detection 2D, memahami perbedaan kompleksitas dan performa antara algoritma Brute Force dan Quadtree, serta menerapkan konsep dasar fisika seperti elastic collision dan pembatasan gerak partikel di dalam ruang simulasi. Selain itu, proyek ini juga berfokus pada pengembangan kreativitas visual dan tuning parameter fisika agar simulasi terlihat lebih realistis dan responsif.

⮞ Tools dan Teknologi : Proyek ini dikembangkan menggunakan bahasa pemrograman C++ dengan library grafis SFML versi 3.0.2 untuk visualisasi. Proses kompilasi dilakukan menggunakan MinGW-w64 (GCC), pengelolaan versi menggunakan Git, dan pengembangan kode dilakukan melalui editor Visual Studio Code atau Code::Blocks.

⮞ Referensi : Referensi utama yang digunakan dalam pengerjaan proyek ini adalah video “Building Collision Simulations: An Introduction to Computer Graphics” dari channel YouTube Reducible dan video “Making a Physics Simulation in C++!” dari channel YouTube Okapidev, yang membahas dasar simulasi fisika dan collision detection dalam konteks Computer Graphics.

⮞ Algoritma Brute Force : Algoritma Brute Force melakukan pengecekan tabrakan dengan membandingkan setiap pasangan partikel yang ada di dalam simulasi. Pendekatan ini sederhana dan mudah diimplementasikan, namun memiliki kompleksitas waktu O(n²) sehingga performanya menurun secara signifikan ketika jumlah partikel meningkat.

⮞ Algoritma Quadtree : Algoritma Quadtree menggunakan pendekatan spatial partitioning dengan membagi ruang simulasi menjadi empat kuadran secara rekursif. Setiap partikel hanya dicek terhadap partikel lain yang berada di area terdekat, sehingga jumlah pengecekan tabrakan dapat dikurangi secara signifikan dan performa simulasi menjadi lebih efisien untuk jumlah partikel yang lebih besar.

⮞ Fitur dan Kreativitas : Simulasi ini menampilkan bubble berukuran besar dengan warna cerah yang bergerak aktif dan responsif. Partikel dibatasi agar tidak keluar dari area simulasi, dilengkapi sistem anti-stuck sehingga partikel tidak diam di pojok, serta menggunakan fixed timestep physics untuk menjaga stabilitas simulasi. Pengguna dapat melakukan peralihan algoritma collision detection secara real-time untuk membandingkan hasil dan performa kedua metode.

⮞ Struktur Folder : Struktur proyek disusun secara modular dengan pemisahan file sumber untuk logika partikel, quadtree, dan program utama, sehingga memudahkan pengembangan dan pemeliharaan kode.

⮞ Cara Build dan Run : Pastikan library SFML telah diekstrak pada direktori C:\SFML. Proyek dapat dikompilasi menggunakan perintah g++ dengan menambahkan path include dan library SFML, kemudian dijalankan melalui executable yang dihasilkan.

⮞ Kontrol Program : Pengguna dapat menekan tombol SPACE untuk melakukan toggle antara algoritma Brute Force dan Quadtree selama simulasi berjalan, serta menutup jendela aplikasi untuk mengakhiri program.

⮞ Hasil dan Analisis Singkat : Berdasarkan hasil simulasi, algoritma Brute Force menunjukkan penurunan performa ketika jumlah partikel meningkat, sedangkan algoritma Quadtree memberikan efisiensi yang lebih baik dengan mengurangi jumlah pengecekan tabrakan. Visualisasi simulasi membantu memahami perbedaan pendekatan kedua algoritma secara intuitif dan praktis.
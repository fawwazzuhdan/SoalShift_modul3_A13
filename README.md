# SoalShift_modul3_A13
  - [Nomor 1](#nomor-1)
  - [Nomor 2](#nomor-2)
  - [Nomor 3](#nomor-3)
  - [Nomor 4](#nomor-4)
  - [Nomor 5](#nomor-5)

## Nomor 1
### Soal
Buatlah program C yang bisa menghitung faktorial secara parallel lalu menampilkan hasilnya secara berurutan
Contoh:

    ./faktorial 5 3 4
    3! = 6
    4! = 24
    5! = 120

### Jawaban
menjalankan program [soal1.c](soal1/soal1.c). Pertama-tama merubah tipe argumen yang asalnya string menjadi integer kemudian disimpan ke dalam array kemudian diurutkan dari terkecil ke terbesar. Setelah itu menjalankan thread untuk mendapatkan hasil faktorial dari setiap argumen yang telah diurutkan di dalam array.

## Nomor 2
### Soal
Pada suatu hari ada orang yang ingin berjualan 1 jenis barang secara private, dia memintamu membuat program C dengan spesifikasi sebagai berikut:
- Terdapat 2 server: server penjual dan server pembeli
- 1 server hanya bisa terkoneksi dengan 1 client
Server penjual dan server pembeli memiliki stok barang yang selalu sama
- Client yang terkoneksi ke server penjual hanya bisa menambah stok
    - Cara menambah stok: client yang terkoneksi ke server penjual mengirim string “tambah” ke server lalu stok bertambah 1
- Client yang terkoneksi ke server pembeli hanya bisa mengurangi stok
    - Cara mengurangi stok: client yang terkoneksi ke server pembeli mengirim string “beli” ke server lalu stok berkurang 1
- Server pembeli akan mengirimkan info ke client yang terhubung dengannya apakah transaksi berhasil atau tidak berdasarkan ketersediaan stok
    - Jika stok habis maka client yang terkoneksi ke server pembeli akan mencetak “transaksi gagal”
    - Jika stok masih ada maka client yang terkoneksi ke server pembeli akan mencetak “transaksi berhasil”
- Server penjual akan mencetak stok saat ini setiap 5 detik sekali
- **Menggunakan thread, socket, shared memory**


### Jawaban
menjalankan semua program yang berada di folder [soal2](soal2/).

### Penjelasan :
- Server penjual
    - Membuat socket untuk menghubungkan ke client penjual
    - Membuat thread untuk menampilkan stock yang tersedia setiap 5 detik
    - Share memory dengan server pembeli
    - Membuat thread untuk mengatur pesan yang diterima atau yang akan dikirim di dalam socket, jika menerima pesan "tambah" maka stock akan bertambah 1
    - Menghitung jumlah koneksi client penjual yang tersambung ke server penjual jika lebih dari satu maka koneksi client penjual ditolak oleh server penjual
- Client penjual
    - Membuat socket untuk menghubungkan ke server penjual
    - Menyambungkan ke server penjual
    - Membuat thread untuk mengatur pesan yang diterima atau yang akan dikirim di dalam socket
- Server pembeli
    - Membuat socket untuk menghubungkan ke client pembeli
    - Share memory dengan server penjual
    Membuat thread untuk mengatur pesan yang diterima atau yang akan dikirim di dalam socket, jika menerima pesan "beli" maka akan dicek terlebih dahulu apakah stock lebih dari 0 apa tidak, jika lebih dari 0 maka stock akan berkurang 1 dan akan mengirimkan pesan "transaksi berhasil" ke client pembeli. jika tidak maka akan mengirimkan pesan "transaksi gagal".
    - Menghitung jumlah koneksi client pembeli yang tersambung ke server pembeli jika lebih dari satu maka koneksi client pembeli ditolak oleh server pembeli
- Client pembeli
    - Membuat socket untuk menghubungkan ke server pembeli
    - Menyambungkan ke server pembeli
    - Membuat thread untuk mengatur pesan yang diterima atau yang akan dikirim di dalam socket


## Nomor 3
### Soal
Agmal dan Iraj merupakan 2 sahabat yang sedang kuliah dan hidup satu kostan, sayangnya mereka mempunyai gaya hidup yang berkebalikan, dimana Iraj merupakan laki-laki yang sangat sehat,rajin berolahraga dan bangun tidak pernah kesiangan sedangkan Agmal hampir menghabiskan setengah umur hidupnya hanya untuk tidur dan ‘ngoding’. Dikarenakan mereka sahabat yang baik, Agmal dan iraj sama-sama ingin membuat satu sama lain mengikuti gaya hidup mereka dengan cara membuat Iraj sering tidur seperti Agmal, atau membuat Agmal selalu bangun pagi seperti Iraj. Buatlah suatu program C untuk menggambarkan kehidupan mereka dengan spesifikasi sebagai berikut:
- Terdapat 2 karakter Agmal dan Iraj
- Kedua karakter memiliki status yang unik
    - Agmal mempunyai WakeUp_Status, di awal program memiliki status 0
    - Iraj memiliki Spirit_Status, di awal program memiliki status 100
    - Terdapat 3 Fitur utama
        - All Status, yaitu menampilkan status kedua sahabat
        Ex: Agmal WakeUp_Status = 75 
            Iraj Spirit_Status = 30
        - “Agmal Ayo Bangun” menambah WakeUp_Status Agmal sebesar 15 point
        - “Iraj Ayo Tidur” mengurangi Spirit_Status Iraj sebanyak 20 point
    - Terdapat Kasus yang unik dimana:
        - Jika Fitur “Agmal Ayo Bangun” dijalankan sebanyak 3 kali, maka Fitur “Iraj Ayo Tidur” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Fitur Iraj Ayo Tidur disabled 10 s”)
        - Jika Fitur  “Iraj Ayo Tidur” dijalankan sebanyak 3 kali, maka Fitur “Agmal Ayo Bangun” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Agmal Ayo Bangun disabled 10 s”)
    - Program akan berhenti jika Salah Satu :
        - WakeUp_Status Agmal >= 100 (Tampilkan Pesan “Agmal Terbangun,mereka bangun pagi dan berolahraga”)
        - Spirit_Status Iraj <= 0 (Tampilkan Pesan “Iraj ikut tidur, dan bangun kesiangan bersama Agmal”)


    - **Syarat Menggunakan Lebih dari 1 Thread**


### Jawaban

## Nomor 4
### Soal
Buatlah sebuah program C dimana dapat menyimpan list proses yang sedang berjalan (ps -aux) maksimal 10 list proses. Dimana awalnya list proses disimpan dalam di 2 file ekstensi .txt yaitu  SimpanProses1.txt di direktori /home/Document/FolderProses1 dan SimpanProses2.txt di direktori /home/Document/FolderProses2 , setelah itu masing2 file di  kompres zip dengan format nama file KompresProses1.zip dan KompresProses2.zip dan file SimpanProses1.txt dan SimpanProses2.txt akan otomatis terhapus, setelah itu program akan menunggu selama 15 detik lalu program akan mengekstrak kembali file KompresProses1.zip dan KompresProses2.zip 

**Dengan Syarat :**
- Setiap list proses yang di simpan dalam masing-masing file .txt harus berjalan bersama-sama
- Ketika mengkompres masing-masing file .txt harus berjalan bersama-sama
- Ketika Mengekstrak file .zip juga harus secara bersama-sama
- Ketika Telah Selesai melakukan kompress file .zip masing-masing file, maka program akan memberi pesan “Menunggu 15 detik untuk mengekstrak kembali”
- Wajib Menggunakan Multithreading
- Boleh menggunakan system


### Jawaban

## Nomor 5
### Soal

### Jawaban

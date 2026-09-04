## Detail Percobaan
Percobaan 1A berfokus pada proses akuisisi data suhu dan kelembapan menggunakan sensor DHT11 yang terhubung dengan ESP8266. Program membaca nilai suhu dan kelembapan secara berkala, kemudian menampilkan hasil pembacaan tersebut melalui Serial Monitor. Program juga melakukan pemeriksaan terhadap data yang diperoleh untuk memastikan sensor berhasil memberikan nilai yang valid.

## Penjelasan Code
Program dimulai dengan memanggil library DHT dan menentukan pin serta jenis sensor yang digunakan. ESP8266 kemudian melakukan inisialisasi komunikasi serial dan sensor DHT11 pada fungsi `setup()`. Pada fungsi `loop()`, program membaca data suhu dan kelembapan dari sensor secara berulang. Hasil pembacaan diperiksa menggunakan fungsi `isnan()`. Jika data tidak valid, program menampilkan pesan kegagalan. Jika data berhasil dibaca, program menampilkan nilai suhu dan kelembapan pada Serial Monitor, kemudian menunggu selama tiga detik sebelum melakukan pembacaan berikutnya.

## Penjelasan Setiap Fungsi
- `setup()`\
Fungsi `setup()` dijalankan satu kali ketika ESP8266 pertama kali dinyalakan atau di-reset. Fungsi ini digunakan untuk memulai komunikasi serial dengan `Serial.begin(115200)` dan menginisialisasi sensor menggunakan `dht.begin()`.

- `loop()`\
Fungsi `loop()` dijalankan secara berulang selama ESP8266 aktif. Pada fungsi ini, program membaca nilai kelembapan menggunakan `dht.readHumidity()` dan suhu menggunakan `dht.readTemperature()`. Program kemudian memeriksa data yang diperoleh dan menampilkan hasil pembacaan melalui Serial Monitor.

- `dht.readHumidity()`\
Fungsi ini digunakan untuk membaca nilai kelembapan udara dari sensor DHT11. Nilai yang diperoleh disimpan ke dalam variabel kelembaban.

- `dht.readTemperature()`\
Fungsi ini digunakan untuk membaca nilai suhu dari sensor DHT11. Nilai yang diperoleh disimpan ke dalam variabel suhu.

- `isnan()`\
Fungsi `isnan()` digunakan untuk memeriksa apakah hasil pembacaan sensor memiliki nilai yang tidak valid atau Not a Number (NaN).

## Penjelasan Percabangan atau Conditional
Program menggunakan percabangan `if-else` untuk memeriksa hasil pembacaan sensor. Kondisi `if (isnan(kelembaban) || isnan(suhu))` akan bernilai benar apabila data kelembapan atau suhu tidak valid.Program kemudian menampilkan pesan bahwa pembacaan sensor gagal. Jika kedua data berhasil dibaca, bagian else akan dijalankan untuk menampilkan nilai suhu dan kelembapan pada Serial Monitor.

## Library atau Dependencies
Program memerlukan library berikut:
1. DHT sensor library, yang digunakan untuk membaca data dari sensor DHT11.
2. Library pendukung yang dibutuhkan oleh DHT sensor library sesuai dengan instalasi library pada Arduino IDE.
3. Board package ESP8266, agar program dapat dikompilasi dan diunggah ke perangkat ESP8266.

Library utama dipanggil dalam program menggunakan: `#include <DHT.h>`

## Jawaban Pertanyaan Percobaan 1A
1. Gambarkan diagram alur (flowchart) proses akuisisi data sensor DHT22 pada program di atas!
- <img width="579" height="802" alt="Diagram Tanpa Judul drawio" src="https://github.com/user-attachments/assets/feb93240-66c0-42ae-a349-ef40ad4b5458" />
2. Apa fungsi dari perintah `isnan()` pada program tersebut?
- Fungsi `isnan()` digunakan untuk memeriksa apakah data yang diperoleh dari sensor memiliki nilai NaN (Not a Number) atau tidak valid. Pada program ini, fungsi tersebut memeriksa hasil pembacaan suhu dan kelembaban sehingga program dapat menampilkan pesan kesalahan apabila sensor gagal memberikan data yang benar. 
3. Jelaskan mengapa diperlukan jeda (delay) minimal sekitar 2 detik antar pembacaan sensor DHT22!
- Jeda diperlukan agar sensor memiliki waktu yang cukup untuk melakukan pembacaan kondisi suhu dan kelembaban sebelum data berikutnya diambil. Jika pembacaan dilakukan terlalu cepat, hasil yang diperoleh dapat menjadi tidak stabil atau pembacaan sensor dapat gagal. Pada program yang digunakan, pembacaan dilakukan setiap 3 detik agar sensor memiliki waktu yang cukup sebelum melakukan pembacaan kembali. 
4. Modifikasi program agar data suhu dan kelembaban dirata-ratakan dari 5 kali pembacaan sebelum ditampilkan, dan berikan penjelasan di setiap baris kode yang ditambahkan dalam bentuk README.md!

```cpp
#include <DHT.h> // Memanggil library DHT untuk menggunakan sensor DHT11

#define DHTPIN 4       // Menentukan GPIO 4 sebagai pin DATA sensor DHT11
#define DHTTYPE DHT11  // Menentukan jenis sensor yang digunakan, yaitu DHT11

DHT dht(DHTPIN, DHTTYPE); // Membuat objek sensor DHT dengan pin dan jenis sensor yang telah ditentukan

void setup() {
  Serial.begin(115200); // Memulai komunikasi serial dengan baud rate 115200
  delay(1000); // Memberikan jeda selama 1 detik

  Serial.println(); // Membuat baris kosong pada Serial Monitor
  Serial.println("Memulai DHT11..."); // Menampilkan informasi bahwa sensor DHT11 akan digunakan

  dht.begin(); // Menginisialisasi sensor DHT11
  delay(2000); // Memberikan jeda selama 2 detik setelah inisialisasi sensor
}

void loop() {

  float totalSuhu = 0; // Menyimpan total dari seluruh pembacaan suhu
  float totalKelembaban = 0; // Menyimpan total dari seluruh pembacaan kelembaban
  int jumlahDataValid = 0; // Menghitung jumlah data yang berhasil dibaca

  for (int i = 0; i < 5; i++) { // Melakukan pembacaan sensor sebanyak 5 kali

    float kelembaban = dht.readHumidity(); // Membaca nilai kelembaban dari sensor
    float suhu = dht.readTemperature(); // Membaca nilai suhu dari sensor

    if (isnan(kelembaban) || isnan(suhu)) { // Memeriksa apakah pembacaan data gagal

      Serial.println("Gagal membaca data dari sensor DHT11!"); // Menampilkan pesan apabila data tidak valid

    } else {

      totalSuhu = totalSuhu + suhu; // Menambahkan nilai suhu ke total suhu
      totalKelembaban = totalKelembaban + kelembaban; // Menambahkan nilai kelembaban ke total kelembaban
      jumlahDataValid++; // Menambahkan jumlah data yang berhasil dibaca
    }

    delay(2000); // Memberikan jeda selama 2 detik sebelum pembacaan berikutnya
  }

  if (jumlahDataValid > 0) { // Memastikan terdapat minimal satu data yang berhasil dibaca

    float rataSuhu = totalSuhu / jumlahDataValid; // Menghitung rata-rata suhu dari data yang valid
    float rataKelembaban = totalKelembaban / jumlahDataValid; // Menghitung rata-rata kelembaban dari data yang valid

    Serial.print("Rata-rata Suhu: "); // Menampilkan teks rata-rata suhu
    Serial.print(rataSuhu); // Menampilkan hasil rata-rata suhu
    Serial.print(" °C | Rata-rata Kelembaban: "); // Menampilkan satuan suhu dan teks kelembaban
    Serial.print(rataKelembaban); // Menampilkan hasil rata-rata kelembaban
    Serial.println(" %"); // Menampilkan satuan persen dan berpindah ke baris berikutnya

  } else {

    Serial.println("Tidak ada data sensor yang berhasil dibaca!"); // Menampilkan pesan apabila semua pembacaan gagal
  }

  delay(3000); // Memberikan jeda sebelum proses rata-rata berikutnya dilakukan
}
```

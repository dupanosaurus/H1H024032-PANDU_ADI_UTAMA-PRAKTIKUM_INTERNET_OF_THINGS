## Detail Percobaan
Percobaan 2A berfokus pada pengendalian aktuator berupa relay berdasarkan data suhu yang diperoleh dari sensor DHT11. ESP8266 membaca nilai suhu dari sensor, kemudian membandingkan nilai tersebut dengan batas suhu yang telah ditentukan, yaitu 30°C. Apabila suhu melebihi nilai ambang, relay akan diaktifkan. Sebaliknya, apabila suhu tidak melebihi nilai tersebut, relay akan dinonaktifkan.

## Penjelasan Code
Program memanggil library DHT, kemudian menentukan pin untuk sensor DHT11 dan relay. Nilai `suhuThreshold` digunakan sebagai batas untuk menentukan kondisi relay. Pada fungsi `setup()`, program memulai komunikasi serial, menginisialisasi sensor, dan mengatur pin relay sebagai output dengan kondisi awal mati. Pada fungsi `loop()`, ESP8266 membaca nilai suhu dari DHT11 dan memeriksa apakah data yang diperoleh valid. Jika pembacaan berhasil, program membandingkan nilai suhu dengan batas 30°C. Relay akan menyala apabila suhu lebih dari 30°C dan akan mati apabila suhu berada pada atau di bawah nilai ambang tersebut.

## Penjelasan Setiap Fungsi
- `setup()`\
Fungsi `setup()` dijalankan satu kali ketika ESP8266 pertama kali dinyalakan atau di-reset. Fungsi ini digunakan untuk memulai komunikasi serial, menginisialisasi sensor DHT11, serta mengatur pin relay sebagai output.

- `loop()`\
Fungsi `loop()` dijalankan secara berulang selama ESP8266 aktif. Program membaca nilai suhu dari sensor, memeriksa validitas data, membandingkan suhu dengan nilai ambang, dan menentukan kondisi relay berdasarkan hasil perbandingan tersebut.

- `dht.readTemperature()`\
Fungsi ini digunakan untuk membaca nilai suhu dari sensor DHT11. Nilai hasil pembacaan disimpan dalam variabel suhu untuk digunakan dalam proses pengambilan keputusan.

- `isnan()`\
Fungsi `isnan()` digunakan untuk memeriksa apakah nilai suhu yang diperoleh dari sensor tidak valid. Program akan menampilkan pesan kesalahan apabila pembacaan sensor menghasilkan nilai yang tidak valid.

- `digitalWrite()`\
Fungsi `digitalWrite()` digunakan untuk mengirimkan sinyal digital ke pin relay. Nilai HIGH digunakan untuk mengaktifkan relay, sedangkan nilai LOW digunakan untuk menonaktifkan relay sesuai dengan konfigurasi program yang digunakan.

- `delay()`\
Fungsi `delay(2000)` memberikan jeda selama dua detik sebelum program melakukan pembacaan suhu kembali.

## Penjelasan Percabangan atau Conditional
Program menggunakan dua percabangan `if-else`. Percabangan pertama, yaitu  `if (isnan(suhu))`, digunakan untuk memeriksa apakah data suhu berhasil dibaca. Apabila data tidak valid, program menampilkan pesan kegagalan. Percabangan kedua membandingkan nilai suhu dengan `suhuThreshold`. Jika suhu lebih dari 30°C, program mengaktifkan relay dan menampilkan status aktuator ON. Jika suhu tidak melebihi 30°C, program menonaktifkan relay dan menampilkan status aktuator OFF.

## Library atau Dependencies
Program memerlukan library dan dependencies berikut:
1. DHT sensor library, yang digunakan untuk membaca data dari sensor DHT11.
2. Library pendukung yang diperlukan oleh DHT sensor library sesuai dengan instalasi library pada Arduino IDE.
3. Board package ESP8266, agar program dapat digunakan pada perangkat ESP8266.

Library utama dipanggil dalam program menggunakan: `#include <DHT.h>`

## Jawaban Pertanyaan Percobaan 2A
1. Mengapa diperlukan nilai ambang batas `(threshold)` dalam sistem kendali aktuator berbasis sensor?
- Nilai ambang batas `(threshold)` diperlukan sebagai batas untuk menentukan kapan aktuator harus memberikan respons terhadap data yang diperoleh dari sensor. Mikrokontroler membandingkan nilai sensor dengan nilai ambang yang telah ditentukan. Apabila kondisi tersebut terpenuhi, mikrokontroler akan memberikan perintah kepada aktuator untuk menyala atau mati. 
2. Jelaskan apa yang akan terjadi apabila nilai `suhuThreshold` diturunkan menjadi sangat rendah, misalnya 20.0!
- Apabila nilai `suhuThreshold` diturunkan menjadi 20.0, relay akan menyala ketika suhu yang terbaca lebih dari 20°C. Akibatnya, aktuator akan lebih sering berada dalam kondisi aktif karena suhu lingkungan yang melebihi 20°C lebih mudah mencapai nilai ambang tersebut. 
3. Apa perbedaan antara kendali aktuator secara terus-menerus (kondisi tunggal) dengan kendali menggunakan histerisis (dua ambang batas)?
- Kendali dengan kondisi tunggal menggunakan satu nilai ambang untuk menentukan kondisi aktuator, sehingga aktuator dapat sering berubah keadaan apabila nilai sensor berada di sekitar ambang tersebut. Kendali menggunakan histerisis memakai dua nilai ambang, yaitu batas untuk menyalakan dan batas untuk mematikan aktuator, sehingga perubahan kondisi aktuator menjadi lebih stabil. 
4. Modifikasi program agar menggunakan dua ambang batas (histerisis), misalnya aktuator menyala pada suhu di atas 30°C dan baru mati pada suhu di bawah 28°C, dan berikan penjelasan di setiap baris kode nya dalam bentuk README.md!

```cpp
#include <DHT.h> // Memanggil library DHT untuk menggunakan sensor DHT11

#define DHTPIN 4       // Menentukan GPIO 4 atau D2 sebagai pin DATA sensor DHT11
#define DHTTYPE DHT11  // Menentukan jenis sensor yang digunakan, yaitu DHT11

#define RELAYPIN 5     // Menentukan GPIO 5 atau D1 sebagai pin input relay

DHT dht(DHTPIN, DHTTYPE); // Membuat objek DHT dengan pin dan jenis sensor yang telah ditentukan

const float suhuOn = 30.0; // Menentukan batas suhu untuk menyalakan aktuator
const float suhuOff = 28.0; // Menentukan batas suhu untuk mematikan aktuator

bool statusAktuator = false; // Menyimpan status aktuator, false untuk mati dan true untuk menyala

void setup() {
  Serial.begin(115200); // Memulai komunikasi serial dengan baud rate 115200

  dht.begin(); // Menginisialisasi sensor DHT11

  pinMode(RELAYPIN, OUTPUT); // Mengatur pin relay sebagai output

  digitalWrite(RELAYPIN, LOW); // Mengatur relay dalam kondisi mati saat sistem pertama kali dijalankan

  Serial.println("Sistem DHT11 + Relay dengan Histerisis"); // Menampilkan informasi sistem
  Serial.println("Menunggu pembacaan sensor..."); // Menampilkan informasi bahwa sistem sedang membaca sensor
}

void loop() {

  float suhu = dht.readTemperature(); // Membaca nilai suhu dari sensor DHT11

  if (isnan(suhu)) { // Memeriksa apakah nilai suhu yang dibaca tidak valid

    Serial.println("Gagal membaca data sensor!"); // Menampilkan pesan apabila pembacaan sensor gagal

  } else {

    Serial.print("Suhu: "); // Menampilkan teks suhu pada Serial Monitor
    Serial.print(suhu); // Menampilkan nilai suhu yang terbaca
    Serial.print(" °C -> "); // Menampilkan satuan suhu dan tanda pemisah

    if (suhu > suhuOn) { // Memeriksa apakah suhu lebih dari 30°C

      statusAktuator = true; // Mengubah status aktuator menjadi menyala

    } else if (suhu < suhuOff) { // Memeriksa apakah suhu kurang dari 28°C

      statusAktuator = false; // Mengubah status aktuator menjadi mati
    }

    if (statusAktuator == true) { // Memeriksa apakah aktuator berada dalam kondisi menyala

      digitalWrite(RELAYPIN, HIGH); // Mengaktifkan relay
      Serial.println("Aktuator: ON"); // Menampilkan status aktuator menyala

    } else {

      digitalWrite(RELAYPIN, LOW); // Menonaktifkan relay
      Serial.println("Aktuator: OFF"); // Menampilkan status aktuator mati
    }
  }

  delay(2000); // Memberikan jeda selama 2 detik sebelum pembacaan berikutnya
}
```

## Detail Percobaan
Percobaan 3A berfokus pada proses pengiriman data dari ESP8266 ke server menggunakan protokol HTTP dengan metode `POST`. Data yang dikirim berupa suhu dan kelembaban dalam format JSON. ESP8266 terlebih dahulu dihubungkan ke jaringan WiFi menggunakan SSID dan password yang telah ditentukan. Setelah berhasil terhubung, ESP8266 membuat koneksi HTTPS menuju endpoint pengujian `https://httpbin.org/post`. Program menggunakan library `ESP8266HTTPClient` untuk mengirimkan request HTTP, `WiFiClientSecure` untuk mendukung koneksi HTTPS, dan `ArduinoJson` untuk menyusun data JSON. Data suhu sebesar `28.5` dan kelembaban sebesar `65.0` dikirimkan ke server. Serial Monitor kemudian menampilkan data JSON yang dikirim, kode response HTTP, serta isi balasan dari server. Pada percobaan ini juga dilakukan modifikasi dengan menambahkan informasi waktu menggunakan fungsi `millis()` ke dalam data JSON.

## Penjelasan Code
Program dimulai dengan memanggil library `ESP8266WiFi` untuk mengakses fitur WiFi pada ESP8266, `ESP8266HTTPClient` untuk melakukan komunikasi HTTP, `WiFiClientSecure` untuk membuat koneksi HTTPS, dan `ArduinoJson` untuk menyusun data dalam format JSON. SSID dan password digunakan sebagai konfigurasi jaringan WiFi, sedangkan `serverUrl` berisi alamat endpoint pengujian HTTP POST. Pada fungsi `setup()`, komunikasi serial dimulai dengan baud rate `115200`, kemudian ESP8266 mencoba terhubung ke jaringan WiFi menggunakan `WiFi.begin()`. Program menunggu sampai koneksi berhasil melalui perulangan `while (WiFi.status() != WL_CONNECTED)`. Setelah terhubung, Serial Monitor menampilkan informasi keberhasilan koneksi dan IP Address ESP8266. Pada fungsi `loop()`, program memeriksa status WiFi sebelum membuat koneksi HTTPS menggunakan `WiFiClientSecure`. Objek `HTTPClient` digunakan untuk memulai koneksi ke server dan menambahkan header `Content-Type` dengan nilai `application/json`. Data suhu dan kelembaban dimasukkan ke dalam objek JSON, kemudian diubah menjadi teks menggunakan `serializeJson()`. Data tersebut dikirim ke server menggunakan metode `http.POST()`. Jika server memberikan response, program menampilkan kode response dan isi balasan. Jika pengiriman gagal, program menampilkan kode error. Setelah selesai, koneksi HTTP ditutup menggunakan `http.end()` dan program menunggu selama 10 detik sebelum mengulangi proses.

## Penjelasan Setiap Fungsi
- `setup()`\
Fungsi `setup()` dijalankan satu kali ketika ESP8266 pertama kali dinyalakan atau di-reset. Fungsi ini digunakan untuk memulai komunikasi serial, menghubungkan ESP8266 ke jaringan WiFi, dan menampilkan informasi koneksi.

- `loop()`\
Fungsi `loop()` dijalankan secara berulang selama ESP8266 aktif. Fungsi ini digunakan untuk memeriksa koneksi WiFi, membuat data JSON, mengirim data menggunakan HTTP POST, menampilkan response server, dan memberikan jeda sebelum pengiriman berikutnya.

- `Serial.begin()`\
Fungsi `Serial.begin()` digunakan untuk memulai komunikasi antara ESP8266 dan Serial Monitor. Pada kode ini, baud rate yang digunakan adalah 115200.

- `WiFi.begin()`\
Fungsi `WiFi.begin()` digunakan untuk memulai proses koneksi ESP8266 ke jaringan WiFi berdasarkan SSID dan password yang telah ditentukan.

- `WiFi.status()`\
Fungsi `WiFi.status()` digunakan untuk memeriksa status koneksi WiFi pada ESP8266. Fungsi ini digunakan untuk mengetahui apakah perangkat sudah terhubung dengan jaringan WiFi atau belum.

- `delay()`\
Fungsi `delay()` digunakan untuk memberikan jeda waktu pada program. Pada kode ini, fungsi tersebut digunakan saat proses koneksi WiFi dan sebelum program melakukan pengiriman data berikutnya.

- `Serial.print()`\
Fungsi `Serial.print()` digunakan untuk menampilkan teks atau data pada Serial Monitor tanpa membuat baris baru.

- `Serial.println()`\
Fungsi `Serial.println()` digunakan untuk menampilkan teks atau data pada Serial Monitor dan langsung membuat baris baru setelah data ditampilkan.

- `WiFi.localIP()`\
Fungsi `WiFi.localIP()` digunakan untuk mengambil alamat IP yang diperoleh ESP8266 setelah berhasil terhubung ke jaringan WiFi.

- `client.setInsecure()`\
Fungsi `client.setInsecure()` digunakan untuk menonaktifkan pemeriksaan sertifikat SSL/TLS pada koneksi HTTPS. Fungsi ini memungkinkan ESP8266 melakukan koneksi HTTPS tanpa memvalidasi sertifikat server.

- `http.begin()`\
Fungsi `http.begin()` digunakan untuk memulai koneksi HTTP atau HTTPS menuju alamat server yang telah ditentukan pada variabel `serverUrl`.

- `http.addHeader()`\
Fungsi `http.addHeader()` digunakan untuk menambahkan header pada permintaan HTTP. Pada kode ini, header yang ditambahkan adalah `Content-Type: application/json` untuk memberi tahu server bahwa data yang dikirim memiliki format JSON.

- `serializeJson()`\
Fungsi `serializeJson()` digunakan untuk mengubah data JSON yang terdapat pada objek `JsonDocument` menjadi bentuk teks JSON yang dapat dikirim melalui jaringan.

- `http.POST()`\
Fungsi `http.POST()` digunakan untuk mengirimkan data ke server menggunakan metode HTTP POST. Pada kode ini, data JSON dikirimkan melalui request body.

- `http.getString()`\
Fungsi `http.getString()` digunakan untuk mengambil isi respons yang dikirimkan oleh server setelah ESP8266 melakukan permintaan HTTP.

- `http.end()`\
Fungsi `http.end()` digunakan untuk mengakhiri koneksi HTTP setelah proses pengiriman dan penerimaan respons dari server selesai.

## Penjelasan Percabangan atau Conditional
Program menggunakan percabangan `if` untuk memeriksa kondisi koneksi WiFi melalui perintah `if (WiFi.status() == WL_CONNECTED)`. Jika kondisi bernilai benar, ESP8266 akan membuat koneksi HTTPS, menyusun data suhu dan kelembaban dalam format JSON, kemudian mengirimkannya ke server menggunakan HTTP POST. Setelah pengiriman dilakukan, program menggunakan percabangan `if-else` untuk memeriksa nilai `httpResponseCode`. Jika nilai tersebut lebih besar dari `0`, berarti server memberikan response sehingga program menampilkan kode HTTP dan isi balasan server. Jika nilainya tidak lebih besar dari `0`, bagian `else` dijalankan dan program menampilkan pesan bahwa pengiriman gagal beserta kode error. Apabila ESP8266 tidak terhubung ke WiFi, proses pengiriman HTTP tidak dijalankan dan program langsung menunggu selama 10 detik sebelum mengulangi fungsi `loop()`.

## Library atau Dependencies
Program memerlukan library dan board package berikut:
1. **ESP8266WiFi**\
   Digunakan untuk menghubungkan ESP8266 ke jaringan WiFi.
2. **ESP8266HTTPClient**\
   Digunakan untuk membuat dan mengirim request HTTP atau HTTPS dari ESP8266 ke server.
3. **WiFiClientSecure**\
   Digunakan untuk mendukung koneksi HTTPS.
4. **ArduinoJson**\
   Digunakan untuk membuat dan mengubah data ke dalam format JSON.
5. **Board package ESP8266**\
   Digunakan agar program dapat dikompilasi dan diunggah ke board ESP8266 melalui Arduino IDE.

Library utama dipanggil dalam program menggunakan:
```cpp
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
```

## Jawaban Pertanyaan Percobaan 3A
1. Gambarkan diagram alur (flowchart) proses pengiriman data melalui HTTP POST pada program di atas!
- <img width="717" height="957" alt="pp" src="https://github.com/user-attachments/assets/d4a08d2e-d886-4870-84e9-3ccd8cbaf6e6" />
2. Apa fungsi dari perintah `http.addHeader("Content-Type", "application/json")` pada program tersebut?
- Kode tersebut berfungsi untuk memberi informasi kepada server bahwa data yang dikirim oleh ESP8266 memiliki format JSON. Dengan begitu, server dapat mengetahui dan memproses isi data sesuai dengan format yang digunakan. 
3. Jelaskan arti dari kode response HTTP 200 dan sebutkan salah satu contoh kode response HTTP lain beserta artinya!
- Kode HTTP 200 menunjukkan bahwa permintaan yang dikirim berhasil diproses oleh server. Contoh kode lainnya adalah HTTP 404, yang berarti halaman atau sumber daya yang diminta tidak ditemukan pada server. 
4. Modifikasi program agar ESP32 dapat mengirimkan data tambahan berupa waktu (dalam milidetik sejak dinyalakan menggunakan `millis()`) ke dalam JSON yang dikirim, dan berikan penjelasan di setiap baris kode yang ditambahkan dalam bentuk README.md!

```cpp
#include <ESP8266WiFi.h>              // Memanggil library untuk menghubungkan ESP8266 ke jaringan WiFi.
#include <ESP8266HTTPClient.h>        // Memanggil library untuk melakukan komunikasi HTTP.
#include <WiFiClientSecure.h>         // Memanggil library untuk membuat koneksi HTTPS yang aman.
#include <ArduinoJson.h>              // Memanggil library untuk membuat dan mengolah data JSON.

// ==========================
// WIFI
// ==========================

const char* ssid = "S24";             // Menyimpan nama jaringan WiFi yang digunakan.
const char* password = "11111111";    // Menyimpan kata sandi jaringan WiFi yang digunakan.

// ==========================
// HTTP SERVER
// ==========================

const char* serverUrl = "https://httpbin.org/post";
// Menyimpan alamat endpoint server yang digunakan untuk pengujian HTTP POST.

// ==========================
// SETUP
// ==========================

void setup() {                         // Fungsi setup dijalankan satu kali saat ESP8266 menyala.

  Serial.begin(115200);                // Memulai komunikasi serial dengan kecepatan 115200 baud.

  // Menghubungkan ke WiFi
  WiFi.begin(ssid, password);          // Memulai koneksi ESP8266 ke jaringan WiFi sesuai SSID dan password.

  Serial.print("Menghubungkan ke WiFi");
  // Menampilkan pesan bahwa ESP8266 sedang mencoba terhubung ke WiFi.

  while (WiFi.status() != WL_CONNECTED) {
    // Mengulang proses selama ESP8266 belum berhasil terhubung ke WiFi.

    delay(500);                        // Memberikan jeda selama 500 milidetik.

    Serial.print(".");                 // Menampilkan tanda titik sebagai indikator proses koneksi.
  }

  Serial.println();                    // Membuat baris baru pada Serial Monitor.

  Serial.println("WiFi berhasil terhubung!");
  // Menampilkan pesan bahwa koneksi WiFi berhasil dilakukan.

  Serial.print("IP ESP8266: ");
  // Menampilkan keterangan alamat IP ESP8266.

  Serial.println(WiFi.localIP());
  // Menampilkan alamat IP lokal yang diperoleh ESP8266 dari jaringan WiFi.
}

// ==========================
// LOOP
// ==========================

void loop() {                           // Fungsi loop dijalankan secara berulang selama ESP8266 aktif.

  if (WiFi.status() == WL_CONNECTED) {
    // Memeriksa apakah ESP8266 masih terhubung ke jaringan WiFi.

    // Client HTTPS
    WiFiClientSecure client;
    // Membuat objek client untuk membangun koneksi HTTPS dengan server.

    // Untuk pengujian
    // tidak melakukan verifikasi sertifikat
    client.setInsecure();
    // Menonaktifkan verifikasi sertifikat SSL/TLS untuk keperluan pengujian.

    HTTPClient http;
    // Membuat objek http untuk mengatur proses komunikasi HTTP.

    // Memulai koneksi ke server
    http.begin(client, serverUrl);
    // Memulai koneksi HTTPS menggunakan objek client dan alamat server.

    // Header JSON
    http.addHeader("Content-Type", "application/json");
    // Memberi tahu server bahwa data yang dikirim memiliki format JSON.

    // ==========================
    // MEMBUAT DATA JSON
    // ==========================

    JsonDocument doc;
    // Membuat objek JSON bernama doc untuk menyimpan data yang akan dikirim.

    doc["suhu"] = 28.5;
    // Menambahkan data suhu dengan nilai 28.5 derajat Celsius ke dalam JSON.

    doc["kelembaban"] = 65.0;
    // Menambahkan data kelembaban dengan nilai 65.0 persen ke dalam JSON.

    doc["waktu"] = millis();
    // Menambahkan data waktu berupa jumlah milidetik sejak ESP8266 dinyalakan.

    // Mengubah JSON menjadi String
    String requestBody;
    // Membuat variabel String untuk menyimpan JSON dalam bentuk teks.

    serializeJson(doc, requestBody);
    // Mengubah objek JSON menjadi teks dan menyimpannya ke requestBody.

    // Menampilkan data yang akan dikirim
    Serial.print("Mengirim data: ");
    // Menampilkan keterangan bahwa data JSON akan dikirim ke server.

    Serial.println(requestBody);
    // Menampilkan isi data JSON yang akan dikirim.

    // ==========================
    // HTTP POST
    // ==========================

    int httpResponseCode = http.POST(requestBody);
    // Mengirim data JSON ke server menggunakan metode HTTP POST.
    // Kode respons dari server disimpan dalam variabel httpResponseCode.

    // ==========================
    // CEK RESPONSE
    // ==========================

    if (httpResponseCode > 0) {
      // Memeriksa apakah proses HTTP menghasilkan kode respons.

      Serial.print("Kode Response HTTP: ");
      // Menampilkan keterangan kode respons HTTP.

      Serial.println(httpResponseCode);
      // Menampilkan kode respons HTTP dari server.

      Serial.println("Isi Response:");
      // Menampilkan keterangan bahwa baris berikutnya berisi balasan server.

      Serial.println(http.getString());
      // Mengambil dan menampilkan isi response body dari server.

    } else {
      // Bagian ini dijalankan jika proses pengiriman data mengalami kegagalan.

      Serial.print("Pengiriman gagal, kode error: ");
      // Menampilkan pesan bahwa pengiriman data gagal.

      Serial.println(httpResponseCode);
      // Menampilkan kode error yang dihasilkan oleh proses HTTP.
    }

    // Mengakhiri koneksi
    http.end();
    // Mengakhiri koneksi HTTP dan membebaskan sumber daya yang digunakan.
  }

  // Kirim setiap 10 detik
  delay(10000);
  // Memberikan jeda selama 10 detik sebelum proses pengiriman diulang.
}
```

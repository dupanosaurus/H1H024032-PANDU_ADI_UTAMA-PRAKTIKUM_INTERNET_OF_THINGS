#include <ESP8266WiFi.h>              // Memanggil library untuk menghubungkan ESP8266 ke jaringan WiFi.
#include <ESP8266HTTPClient.h>        // Memanggil library untuk melakukan komunikasi HTTP.
#include <WiFiClientSecure.h>         // Memanggil library untuk membuat koneksi HTTPS yang aman.
#include <ArduinoJson.h>              // Memanggil library untuk membuat dan mengolah data JSON.

// ==========================
// WIFI
// ==========================

const char* ssid = "S24";              // Menyimpan nama jaringan WiFi yang digunakan.
const char* password = "11111111";     // Menyimpan kata sandi jaringan WiFi yang digunakan.

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
  WiFi.begin(ssid, password);           // Memulai koneksi ESP8266 ke jaringan WiFi sesuai SSID dan password.

  Serial.print("Menghubungkan ke WiFi");
  // Menampilkan pesan bahwa ESP8266 sedang mencoba terhubung ke WiFi.

  while (WiFi.status() != WL_CONNECTED) {
    // Mengulang proses selama ESP8266 belum berhasil terhubung ke WiFi.

    delay(500);                         // Memberikan jeda selama 500 milidetik.

    Serial.print(".");                  // Menampilkan tanda titik sebagai indikator proses koneksi.
  }

  Serial.println();                     // Membuat baris baru pada Serial Monitor.

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

void loop() {                            // Fungsi loop dijalankan secara berulang selama ESP8266 aktif.

  if (WiFi.status() == WL_CONNECTED) {
    // Memeriksa apakah ESP8266 masih terhubung ke jaringan WiFi.

    // Client HTTPS
    WiFiClientSecure client;
    // Membuat objek client untuk membangun koneksi HTTPS dengan server.

    // Untuk pengujian
    // tidak melakukan verifikasi sertifikat
    client.setInsecure();
    // Menonaktifkan verifikasi sertifikat SSL/TLS untuk keperluan pengujian.
    // Penggunaan ini tidak disarankan untuk sistem IoT yang diterapkan secara nyata.

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
      // Server httpbin.org/post akan mengembalikan data JSON yang telah dikirim.

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


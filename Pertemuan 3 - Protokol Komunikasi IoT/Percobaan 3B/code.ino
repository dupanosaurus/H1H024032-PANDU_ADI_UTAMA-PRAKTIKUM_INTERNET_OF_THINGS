#include <ESP8266WiFi.h>              // Memanggil library untuk menghubungkan ESP8266 ke jaringan WiFi.
#include <PubSubClient.h>             // Memanggil library untuk melakukan komunikasi MQTT.
#include <ArduinoJson.h>              // Memanggil library untuk membuat dan mengolah data JSON.

// ==========================
// WIFI
// ==========================

const char* ssid = "S24";              // Menyimpan nama jaringan WiFi yang digunakan.
const char* password = "11111111";     // Menyimpan kata sandi jaringan WiFi yang digunakan.

// ==========================
// MQTT
// ==========================

const char* mqttServer = "broker.hivemq.com";
// Menyimpan alamat broker MQTT yang digunakan sebagai perantara komunikasi.

const int mqttPort = 1883;
// Menyimpan nomor port MQTT. Port 1883 digunakan untuk komunikasi MQTT tanpa enkripsi TLS.

const char* mqttTopic = "ardhis/esp8266/latihan";
// Menentukan topic MQTT yang digunakan sebagai alamat pengiriman data.
// Subscriber harus menggunakan topic yang sama agar dapat menerima data.

// ==========================
// OBJECT
// ==========================

WiFiClient espClient;
// Membuat objek client untuk komunikasi jaringan antara ESP8266 dan broker MQTT.

PubSubClient client(espClient);
// Membuat objek client MQTT menggunakan koneksi jaringan dari espClient.

// ==========================
// HUBUNGKAN WIFI
// ==========================

void hubungkanWiFi() {
  // Membuat fungsi untuk menghubungkan ESP8266 ke jaringan WiFi.

  WiFi.begin(ssid, password);
  // Memulai koneksi ESP8266 ke jaringan WiFi menggunakan SSID dan password.

  Serial.print("Menghubungkan ke WiFi");
  // Menampilkan pesan bahwa ESP8266 sedang mencoba terhubung ke WiFi.

  while (WiFi.status() != WL_CONNECTED) {
    // Mengulang proses selama ESP8266 belum berhasil terhubung ke WiFi.

    delay(500);
    // Memberikan jeda selama 500 milidetik agar proses tidak berjalan terlalu cepat.

    Serial.print(".");
    // Menampilkan tanda titik sebagai indikator proses koneksi.
  }

  Serial.println();
  // Membuat baris baru pada Serial Monitor.

  Serial.println("WiFi berhasil terhubung!");
  // Menampilkan pesan bahwa koneksi WiFi berhasil dilakukan.

  Serial.print("IP ESP8266: ");
  // Menampilkan keterangan alamat IP ESP8266.

  Serial.println(WiFi.localIP());
  // Menampilkan alamat IP lokal yang diperoleh ESP8266 dari jaringan WiFi.
}

// ==========================
// HUBUNGKAN MQTT
// ==========================

void hubungkanMQTT() {
  // Membuat fungsi untuk menghubungkan ESP8266 ke broker MQTT.

  while (!client.connected()) {
    // Mengulang proses selama ESP8266 belum terhubung ke broker MQTT.

    Serial.print("Menghubungkan ke broker MQTT...");
    // Menampilkan pesan bahwa ESP8266 sedang mencoba terhubung ke broker.

    String clientId = "ESP8266Client-";
    // Membuat variabel String sebagai awalan identitas client MQTT.

    clientId += String(ESP.getChipId(), HEX);
    // Menambahkan ID chip ESP8266 dalam format hexadecimal ke clientId.
    // ID ini digunakan agar identitas client MQTT menjadi lebih unik.

    if (client.connect(clientId.c_str())) {
      // Mencoba menghubungkan client MQTT ke broker menggunakan clientId.
      // Fungsi c_str() mengubah String menjadi format karakter yang dibutuhkan library.

      Serial.println("berhasil terhubung!");
      // Menampilkan pesan jika koneksi ke broker MQTT berhasil.

    } else {
      // Bagian ini dijalankan jika koneksi ke broker MQTT gagal.

      Serial.print("gagal, rc=");
      // Menampilkan pesan kegagalan beserta kode status koneksi.

      Serial.print(client.state());
      // Menampilkan kode status koneksi MQTT untuk mengetahui penyebab kegagalan.

      Serial.println(" coba lagi dalam 2 detik");
      // Menampilkan informasi bahwa program akan mencoba kembali setelah 2 detik.

      delay(2000);
      // Memberikan jeda selama 2 detik sebelum mencoba koneksi kembali.
    }
  }
}

// ==========================
// SETUP
// ==========================

void setup() {
  // Fungsi setup dijalankan satu kali saat ESP8266 menyala atau melakukan reset.

  Serial.begin(115200);
  // Memulai komunikasi serial dengan kecepatan 115200 baud.

  hubungkanWiFi();
  // Memanggil fungsi hubungkanWiFi() untuk menghubungkan ESP8266 ke jaringan WiFi.

  client.setServer(mqttServer, mqttPort);
  // Mengatur alamat broker MQTT dan port yang akan digunakan oleh client.
}

// ==========================
// LOOP
// ==========================

void loop() {
  // Fungsi loop dijalankan secara berulang selama ESP8266 aktif.

  if (!client.connected()) {
    // Memeriksa apakah koneksi ESP8266 ke broker MQTT terputus.

    hubungkanMQTT();
    // Memanggil fungsi hubungkanMQTT() jika client belum terhubung ke broker.
  }

  client.loop();
  // Menjaga komunikasi MQTT tetap berjalan dan memproses koneksi serta pesan MQTT.

// ==========================
// MEMBUAT DATA JSON
// ==========================

  JsonDocument doc;
  // Membuat objek JSON bernama doc untuk menyimpan data yang akan dikirim.

  doc["suhu"] = 28.5;
  // Menambahkan data suhu dengan nilai 28.5 derajat Celsius ke dalam JSON.

  doc["kelembaban"] = 65.0;
  // Menambahkan data kelembaban dengan nilai 65.0 persen ke dalam JSON.

  char buffer[128];
  // Membuat array karakter berukuran 128 karakter untuk menyimpan data JSON
  // sebelum dipublikasikan ke broker MQTT.

  serializeJson(doc, buffer);
  // Mengubah objek JSON doc menjadi teks dan menyimpannya ke dalam buffer.

// ==========================
// PUBLISH KE MQTT
// ==========================

  bool berhasil = client.publish(mqttTopic, buffer);
  // Mengirimkan data JSON ke topic MQTT yang telah ditentukan.
  // Nilai true disimpan ke variabel berhasil jika data berhasil dipublikasikan.

  if (berhasil) {
    // Memeriksa apakah proses publish data berhasil dilakukan.

    Serial.print("Data terkirim ke topic ");
    // Menampilkan keterangan bahwa data berhasil dikirim ke topic MQTT.

    Serial.print(mqttTopic);
    // Menampilkan nama topic MQTT yang digunakan.

    Serial.print(": ");
    // Menampilkan tanda pemisah antara topic dan isi data JSON.

    Serial.println(buffer);
    // Menampilkan isi data JSON yang berhasil dipublikasikan.

  } else {
    // Bagian ini dijalankan jika proses publish data gagal.

    Serial.println("Gagal mengirim data!");
    // Menampilkan pesan bahwa data JSON gagal dikirim ke broker MQTT.
  }

  // Publish setiap 5 detik
  delay(5000);
  // Memberikan jeda selama 5 detik sebelum data berikutnya dipublikasikan.
}

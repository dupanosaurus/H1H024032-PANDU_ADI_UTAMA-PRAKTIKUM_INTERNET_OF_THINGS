## Detail Percobaan
Percobaan 4B berfokus pada proses pertukaran data dua arah antara ESP8266 dan MQTT broker, yaitu ESP8266 mengirimkan data sensor sekaligus menerima perintah untuk mengendalikan aktuator. ESP8266 terlebih dahulu dihubungkan ke jaringan WiFi, kemudian membuat koneksi ke MQTT broker `broker.hivemq.com` menggunakan port `1883`. Program menggunakan library `PubSubClient` untuk komunikasi MQTT, `ArduinoJson` untuk mengolah data JSON, dan `DHT` untuk membaca sensor DHT11. Data suhu dari DHT11 pada GPIO4 dipublish setiap 5 detik ke topic `unsoed/tk245004/viodupan/data`, sedangkan perintah diterima melalui topic `unsoed/tk245004/viodupan/perintah`. Perintah `"ON"` digunakan untuk menyalakan LED pada GPIO5 dan perintah `"OFF"` digunakan untuk mematikannya. Pengiriman data menggunakan `millis()` sehingga program tidak menggunakan `delay()` pada proses publish dan `client.loop()` tetap dapat berjalan untuk memproses pesan MQTT yang masuk. Pada hasil pengamatan, data suhu berhasil dipublish dan perintah ON/OFF berhasil diterima oleh subscriber serta mengubah kondisi LED sesuai perintah.

## Penjelasan Code
Program dimulai dengan memanggil library `ESP8266WiFi` untuk menghubungkan ESP8266 ke jaringan WiFi, `PubSubClient` untuk melakukan komunikasi MQTT, `ArduinoJson` untuk membuat dan membaca data JSON, serta `DHT` untuk membaca sensor DHT11. Variabel `topicData` digunakan sebagai topic untuk mengirim data suhu, sedangkan `topicPerintah` digunakan untuk menerima perintah pengendalian LED. Sensor DHT11 menggunakan GPIO4 dan LED menggunakan GPIO5. Variabel `waktuTerakhirPublish` digunakan untuk menyimpan waktu pengiriman data terakhir, sedangkan `intervalPublish` menentukan interval pengiriman setiap 5 detik. Fungsi `callback()` digunakan untuk menerima pesan MQTT, mengubah payload menjadi `String`, melakukan parsing JSON, dan mengambil nilai `perintah` untuk mengendalikan LED. Fungsi `hubungkanWiFi()` digunakan untuk menghubungkan ESP8266 ke WiFi, sedangkan `hubungkanMQTT()` digunakan untuk membuat koneksi ke broker dan melakukan subscribe pada topic perintah. Pada `setup()`, komunikasi Serial, pin LED, sensor DHT11, WiFi, MQTT broker, dan callback dikonfigurasi. Pada `loop()`, program memeriksa koneksi MQTT dan menjalankan `client.loop()`, kemudian menggunakan `millis()` untuk memeriksa apakah interval 5 detik telah tercapai. Jika interval terpenuhi, sensor DHT11 membaca suhu, data dimasukkan ke dalam JSON, kemudian dikirim ke MQTT broker menggunakan `client.publish()`.

## Penjelasan Setiap Fungsi
- `setup()`\
Fungsi `setup()` dijalankan satu kali ketika ESP8266 pertama kali dinyalakan atau di-reset. Fungsi ini digunakan untuk memulai komunikasi Serial, mengatur pin LED, memulai sensor DHT11, menghubungkan ESP8266 ke WiFi, mengatur MQTT broker, dan mendaftarkancallback.

- `loop()`\
Fungsi `loop()` dijalankan secara berulang selama ESP8266 aktif. Fungsi ini digunakan untuk memeriksa koneksi MQTT, memproses pesan yang masuk, membaca sensor DHT11, membuat data JSON, dan mengirim data suhu setiap 5 detik.

- `callback()`\
Fungsi `callback()` dipanggil ketika ESP8266 menerima pesan dari topic MQTT yang telah di-subscribe. Fungsi ini membaca payload, melakukan parsing JSON, mengambil nilai `perintah`, dan mengatur kondisi LED berdasarkan perintah yang diterima.

- `hubungkanWiFi()`\
Fungsi `hubungkanWiFi()` digunakan untuk menghubungkan ESP8266 ke jaringan WiFi menggunakan SSID dan password yang telah ditentukan.

- `hubungkanMQTT()`\
Fungsi `hubungkanMQTT()` digunakan untuk membuat koneksi antara ESP8266 dan MQTT broker. Setelah berhasil terhubung, fungsi ini melakukan subscribe pada topic perintah.

- `Serial.begin()`\
Fungsi `Serial.begin()` digunakan untuk memulai komunikasi antara ESP8266 dan Serial Monitor. Pada program ini digunakan baud rate 115200.

- `WiFi.begin()`\
Fungsi `WiFi.begin()` digunakan untuk memulai proses koneksi ESP8266 ke jaringan WiFi berdasarkan SSID dan password.

- `WiFi.status()`\
Fungsi `WiFi.status()` digunakan untuk memeriksa status koneksi WiFi pada ESP8266.

- `WiFi.localIP()`\
Fungsi `WiFi.localIP()` digunakan untuk mendapatkan alamat IP ESP8266 setelah berhasil terhubung ke WiFi.

- `client.setServer()`\
Fungsi `client.setServer()` digunakan untuk menentukan alamat dan port MQTT broker yang digunakan oleh MQTT client.

- `client.setCallback()`\
Fungsi `client.setCallback()` digunakan untuk mendaftarkan fungsi `callback()` sebagai pengolah pesan MQTT yang masuk.

- `client.connect()`\
Fungsi `client.connect()` digunakan untuk membuat koneksi ESP8266 dengan MQTT broker menggunakan Client ID.

- `client.subscribe()`\
Fungsi `client.subscribe()` digunakan untuk berlangganan pada topic MQTT tertentu agar ESP8266 dapat menerima pesan dari topic tersebut.

- `client.connected()`\
Fungsi `client.connected()` digunakan untuk memeriksa apakah MQTT client masih terhubung dengan broker.

- `client.loop()`\
Fungsi `client.loop()` digunakan untuk memproses pesan MQTT yang masuk sekaligus menjaga koneksi MQTT tetap aktif. Fungsi ini perlu dipanggil secara berkala agar komunikasi MQTT dapat berjalan dengan baik.

- `millis()`\
Fungsi `millis()` digunakan untuk mendapatkan waktu yang telah berlalu sejak ESP8266 mulai berjalan. Pada program ini digunakan untuk menentukan interval pengiriman data sensor setiap 5 detik tanpa menghentikan proses utama program.

- `dht.begin()`\
Fungsi `dht.begin()` digunakan untuk memulai sensor DHT11 sebelum sensor digunakan untuk membaca data.

- `dht.readTemperature()`\
Fungsi `dht.readTemperature()` digunakan untuk membaca nilai suhu dari sensor DHT11.

- `isnan()`\
Fungsi `isnan()` digunakan untuk memeriksa apakah hasil pembacaan suhu merupakan nilai yang tidak valid atau bukan angka.

- `serializeJson()`\
Fungsi `serializeJson()` digunakan untuk mengubah data pada objek `JsonDocument` menjadi teks JSON yang dapat dikirim melalui MQTT.

- `client.publish()`\
Fungsi `client.publish()` digunakan untuk mengirimkan data JSON suhu ke topic MQTT yang telah ditentukan. PubSubClient menyediakan fungsi `publish()` untuk mengirim payload ke topic tertentu.

- `deserializeJson()`\
Fungsi `deserializeJson()` digunakan untuk mengubah teks JSON yang diterima dari MQTT menjadi data yang dapat diproses oleh program.

- `digitalWrite()`\
Fungsi `digitalWrite()` digunakan untuk memberikan kondisi `HIGH` atau `LOW` pada pin digital. Pada program ini digunakan untuk menyalakan dan mematikan LED.

- `delay()`\
Fungsi `delay()` digunakan pada proses koneksi WiFi dan percobaan koneksi ulang MQTT. Pada proses publish data sensor, program menggunakan `millis()` sehingga tidak menggunakan `delay()` untuk menentukan interval pengiriman.

- `Serial.print()`\
Fungsi `Serial.print()` digunakan untuk menampilkan teks atau data pada Serial Monitor tanpa membuat baris baru.

- `Serial.println()`\
Fungsi `Serial.println()` digunakan untuk menampilkan teks atau data pada Serial Monitor kemudian membuat baris baru.

## Penjelasan Percabangan atau Conditional
Program menggunakan beberapa percabangan `if` untuk menentukan kondisi koneksi, pembacaan sensor, dan perintah yang diterima. Pada fungsi `callback()`, percabangan `if (error)` digunakan untuk memeriksa hasil parsing JSON dan jika terjadi error program menampilkan pesan kegagalan kemudian menjalankan `return`. Setelah JSON berhasil diproses, percabangan `if-else` digunakan untuk memeriksa nilai `perintah`, yaitu `"ON"` untuk menyalakan LED dan `"OFF"` untuk mematikannya, sedangkan perintah lain akan dianggap tidak dikenali. Pada fungsi `loop()`, percabangan `if (!client.connected())` digunakan untuk memeriksa koneksi MQTT dan menjalankan `hubungkanMQTT()` jika koneksi terputus. Selanjutnya, percabangan `if (millis() - waktuTerakhirPublish >= intervalPublish)` digunakan untuk menentukan apakah sudah mencapai interval 5 detik sehingga data sensor dapat dikirim. Setelah suhu dibaca, `if (isnan(suhu))` digunakan untuk memeriksa apakah pembacaan DHT11 gagal. Pada proses publish, `if (client.publish(topicData, buffer))` digunakan untuk memeriksa keberhasilan pengiriman data, sedangkan bagian `else` menampilkan pesan apabila pengiriman gagal.

## Library atau Dependencies
Program memerlukan library dan board package berikut:
1. **ESP8266WiFi**\
   Digunakan untuk menghubungkan ESP8266 ke jaringan WiFi.
2. **PubSubClient**\
   Digunakan untuk melakukan komunikasi MQTT antara ESP8266 dan MQTT broker, termasuk proses koneksi, subscribe, penerimaan pesan melalui callback, dan pemeliharaan koneksi menggunakan `client.loop()`.
3. **ArduinoJson**\
   Digunakan untuk membaca dan memproses data yang dikirim dalam format JSON.
4. **DHT**\
   Digunakan untuk membaca data suhu dari sensor DHT11. 
5. **Board package ESP8266**\
   Digunakan agar program dapat dikompilasi dan diunggah ke board ESP8266 melalui Arduino IDE.

Library utama dipanggil dalam program menggunakan:
```cpp
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <DHT.h>
```

## Jawaban Pertanyaan Percobaan 4B
1. Mengapa penggunaan `delay()` yang lama sebaiknya dihindari pada program yang menggabungkan proses publish dan subscribe secara bersamaan?
- Penggunaan `delay()` yang terlalu lama sebaiknya dihindari karena dapat menghambat proses komunikasi MQTT. Selama `delay()`, program tidak dapat segera menjalankan `client.loop()` untuk memproses pesan yang masuk. Akibatnya, pesan dapat terlambat diproses dan respons aktuator menjadi tidak cepat.
2. Jelaskan cara kerja mekanisme non-blocking menggunakan fungsi `millis()` pada program di atas!
- `millis()` digunakan untuk menghitung waktu yang telah berlalu tanpa menghentikan program seperti `delay()`. Program membandingkan waktu sekarang dengan waktu terakhir publish. Jika selisihnya sudah mencapai interval, misalnya 5 detik, data sensor dikirim dan waktu terakhir diperbarui. Selama menunggu, `client.loop()` tetap berjalan sehingga pesan MQTT tetap dapat diterima.
3. Apa yang akan terjadi apabila fungsi `client.loop()` jarang dipanggil (misalnya hanya sekali setiap 10 detik)?
- Jika `client.loop()` hanya dipanggil setiap 10 detik, pesan MQTT yang masuk akan terlambat diproses sehingga respons aktuator tidak berjalan secara cepat. Selain itu, pemanggilan yang terlalu jarang dapat mengganggu pemeliharaan koneksi MQTT. Karena itu, `client.loop()` perlu dipanggil secara rutin. 
4. Modifikasi program agar menambahkan satu topic perintah baru untuk mengendalikan aktuator kedua (misalnya buzzer), dengan fungsi `callback` yang dapat membedakan topic mana yang menerima pesan, dan berikan penjelasan di setiap baris kode yang ditambahkan dalam bentuk README.md!

```cpp
#include <ESP8266WiFi.h>       // Library untuk koneksi WiFi ESP8266
#include <PubSubClient.h>      // Library untuk komunikasi MQTT
#include <ArduinoJson.h>        // Library untuk membaca dan membuat JSON
#include <DHT.h>                // Library untuk sensor DHT11

// ==================================================
// WIFI
// ==================================================

const char* ssid = "S24";              // Nama jaringan WiFi
const char* password = "11111111";     // Password WiFi

// ==================================================
// MQTT
// ==================================================

const char* mqttServer = "broker.hivemq.com"; // Alamat MQTT broker
const int mqttPort = 1883;                    // Port MQTT

const char* topicData =
    "unsoed/tk245004/viodupan/data";          // Topic untuk mengirim data sensor

const char* topicPerintah =
    "unsoed/tk245004/viodupan/perintah";      // Topic untuk mengendalikan LED

// ==================================================
// TAMBAHAN: TOPIC BUZZER
// ==================================================

const char* topicBuzzer =
    "unsoed/tk245004/viodupan/buzzer";
// Topic MQTT baru khusus untuk mengendalikan buzzer

// ==================================================
// SENSOR DHT11
// ESP8266: D2 = GPIO4
// ==================================================

#define DHTPIN 4                  // Pin DHT11 menggunakan GPIO4/D2
#define DHTTYPE DHT11             // Menentukan jenis sensor adalah DHT11

DHT dht(DHTPIN, DHTTYPE);         // Membuat objek sensor DHT11

// ==================================================
// LED / AKTUATOR
// ESP8266: GPIO5
// ==================================================

const int ledPin = 5;             // LED menggunakan GPIO5/D1

// ==================================================
// TAMBAHAN: BUZZER / AKTUATOR KEDUA
// ESP8266: GPIO14 = D5
// ==================================================

const int buzzerPin = 14;
// Menentukan GPIO14/D5 sebagai pin untuk buzzer

// ==================================================
// MQTT CLIENT
// ==================================================

WiFiClient espClient;             // Membuat koneksi WiFi sebagai client
PubSubClient client(espClient);   // Membuat MQTT client

// ==================================================
// TIMER PUBLISH
// ==================================================

unsigned long waktuTerakhirPublish = 0;
// Menyimpan waktu terakhir data sensor dikirim

const long intervalPublish = 5000;
// Menentukan interval publish selama 5000 ms atau 5 detik

// ==================================================
// CALLBACK MQTT
// Dipanggil ketika pesan dari topic yang di-subscribe diterima
// ==================================================

void callback(char* topic, byte* payload, unsigned int length) {

  String pesan;
  // Variabel untuk menyimpan payload MQTT sebagai String

  // Mengubah payload MQTT menjadi String
  for (unsigned int i = 0; i < length; i++) {

    pesan += (char)payload[i];
    // Mengambil setiap karakter payload dan memasukkannya ke pesan
  }

  // Menampilkan pesan yang diterima
  Serial.println();
  Serial.println("===== PESAN PERINTAH =====");

  Serial.print("Topic   : ");
  Serial.println(topic);
  // Menampilkan topic tempat pesan diterima

  Serial.print("Pesan   : ");
  Serial.println(pesan);
  // Menampilkan isi pesan JSON

  // ==================================================
  // DESERIALISASI JSON
  // ==================================================

  JsonDocument doc;
  // Membuat tempat untuk menyimpan data JSON

  DeserializationError error =
      deserializeJson(doc, pesan);
  // Mengubah String JSON menjadi data yang dapat diproses

  if (error) {
    // Mengecek apakah proses parsing JSON gagal

    Serial.print("Parsing : GAGAL - ");
    Serial.println(error.c_str());
    // Menampilkan jenis kesalahan JSON

    return;
    // Menghentikan callback jika JSON tidak valid
  }

  // Mengambil nilai "perintah" dari JSON
  const char* perintah = doc["perintah"];

  // ==================================================
  // TAMBAHAN: MEMBEDAKAN TOPIC
  // ==================================================

  if (String(topic) == topicPerintah) {
    // Mengecek apakah pesan berasal dari topic LED

    // ==================================================
    // KONTROL LED
    // ==================================================

    if (String(perintah) == "ON") {
      // Jika perintah adalah ON, LED dinyalakan

      digitalWrite(ledPin, HIGH);
      // Memberikan kondisi HIGH pada pin LED

      Serial.println("Aktuator: LED ON");
      // Menampilkan status LED
    }

    else if (String(perintah) == "OFF") {
      // Jika perintah adalah OFF, LED dimatikan

      digitalWrite(ledPin, LOW);
      // Memberikan kondisi LOW pada pin LED

      Serial.println("Aktuator: LED OFF");
      // Menampilkan status LED
    }

    else {
      // Jika perintah bukan ON atau OFF

      Serial.println("Aktuator: Perintah LED tidak dikenali");
      // Menampilkan pesan kesalahan perintah
    }
  }

  // ==================================================
  // TAMBAHAN: KONTROL BUZZER
  // ==================================================

  else if (String(topic) == topicBuzzer) {
    // Mengecek apakah pesan berasal dari topic buzzer

    if (String(perintah) == "ON") {
      // Jika perintah adalah ON, buzzer dinyalakan

      digitalWrite(buzzerPin, HIGH);
      // Memberikan kondisi HIGH pada pin buzzer

      Serial.println("Aktuator: BUZZER ON");
      // Menampilkan status buzzer
    }

    else if (String(perintah) == "OFF") {
      // Jika perintah adalah OFF, buzzer dimatikan

      digitalWrite(buzzerPin, LOW);
      // Memberikan kondisi LOW pada pin buzzer

      Serial.println("Aktuator: BUZZER OFF");
      // Menampilkan status buzzer
    }

    else {
      // Jika perintah bukan ON atau OFF

      Serial.println("Aktuator: Perintah buzzer tidak dikenali");
      // Menampilkan pesan kesalahan perintah
    }
  }

  Serial.println("==========================");
}

// ==================================================
// MENGHUBUNGKAN ESP8266 KE WIFI
// ==================================================

void hubungkanWiFi() {

  WiFi.begin(ssid, password);
  // Memulai koneksi ke jaringan WiFi

  Serial.print("Menghubungkan ke WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    // Menunggu sampai ESP8266 berhasil terhubung

    delay(500);
    // Menunggu 500 ms

    Serial.print(".");
    // Menampilkan titik sebagai indikator koneksi
  }

  Serial.println();
  Serial.println("WiFi berhasil terhubung!");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  // Menampilkan IP Address ESP8266
}

// ==================================================
// MENGHUBUNGKAN ESP8266 KE MQTT BROKER
// ==================================================

void hubungkanMQTT() {

  while (!client.connected()) {
    // Mengulang koneksi jika MQTT belum terhubung

    Serial.print("Menghubungkan ke MQTT... ");

    // Membuat Client ID secara acak
    String clientId =
        "ESP8266Client-" +
        String(random(0xffff), HEX);

    // Mencoba terhubung ke broker
    if (client.connect(clientId.c_str())) {

      Serial.println("berhasil!");

      // ==================================================
      // SUBSCRIBE TOPIC LED
      // ==================================================

      if (client.subscribe(topicPerintah)) {
        // Berlangganan topic untuk mengendalikan LED

        Serial.print("Subscribe berhasil: ");
        Serial.println(topicPerintah);
      }

      // ==================================================
      // TAMBAHAN: SUBSCRIBE TOPIC BUZZER
      // ==================================================

      if (client.subscribe(topicBuzzer)) {
        // Berlangganan topic untuk mengendalikan buzzer

        Serial.print("Subscribe berhasil: ");
        Serial.println(topicBuzzer);
      }
    }

    else {

      Serial.print("gagal, rc=");
      Serial.println(client.state());
      // Menampilkan kode kesalahan koneksi MQTT

      Serial.println("Mencoba kembali dalam 2 detik...");

      delay(2000);
      // Menunggu 2 detik sebelum mencoba kembali
    }
  }
}

// ==================================================
// SETUP
// ==================================================

void setup() {

  Serial.begin(115200);
  // Memulai komunikasi Serial

  // Mengatur LED sebagai OUTPUT
  pinMode(ledPin, OUTPUT);
  // Menjadikan GPIO5 sebagai output

  // Kondisi awal LED mati
  digitalWrite(ledPin, LOW);

  // ==================================================
  // TAMBAHAN: MENGATUR BUZZER
  // ==================================================

  pinMode(buzzerPin, OUTPUT);
  // Menjadikan GPIO14 sebagai output untuk buzzer

  digitalWrite(buzzerPin, LOW);
  // Kondisi awal buzzer mati

  // Memulai sensor DHT11
  dht.begin();

  // Menghubungkan ke WiFi
  hubungkanWiFi();

  // Mengatur MQTT broker
  client.setServer(mqttServer, mqttPort);

  // Mendaftarkan callback MQTT
  client.setCallback(callback);
  // callback() akan dijalankan ketika pesan MQTT diterima
}

// ==================================================
// LOOP
// ==================================================

void loop() {

  // ==================================================
  // CEK KONEKSI MQTT
  // ==================================================

  if (!client.connected()) {
    // Mengecek apakah koneksi MQTT masih aktif

    hubungkanMQTT();
    // Jika terputus, ESP8266 menghubungkan kembali
  }

  // Memproses pesan MQTT yang masuk
  client.loop();
  // Menangani pesan MQTT dan menjaga koneksi tetap aktif

  // ==================================================
  // PUBLISH DATA SENSOR SETIAP 5 DETIK
  // ==================================================

  if (millis() - waktuTerakhirPublish >= intervalPublish) {
    // Mengecek apakah sudah 5 detik sejak publish terakhir

    waktuTerakhirPublish = millis();
    // Menyimpan waktu publish terbaru

    // Membaca suhu dari DHT11
    float suhu = dht.readTemperature();

    // Mengecek apakah pembacaan berhasil
    if (isnan(suhu)) {

      Serial.println("Gagal membaca sensor DHT11!");

      return;
      // Menghentikan proses loop saat pembacaan sensor gagal
    }

    // ==================================================
    // MEMBUAT DATA JSON
    // ==================================================

    JsonDocument doc;
    // Membuat objek untuk menyimpan data JSON

    doc["suhu"] = suhu;
    // Memasukkan nilai suhu ke dalam JSON

    char buffer[128];
    // Menyediakan tempat untuk menyimpan hasil JSON

    serializeJson(doc, buffer);
    // Mengubah data JSON menjadi String untuk dikirim melalui MQTT

    // ==================================================
    // PUBLISH KE MQTT
    // ==================================================

    if (client.publish(topicData, buffer)) {
      // Mengirim data suhu ke topic data

      Serial.print("Data terkirim: ");
      Serial.println(buffer);
      // Menampilkan data JSON yang berhasil dikirim

    }

    else {

      Serial.println("Gagal mengirim data!");
      // Menampilkan pesan jika publish gagal
    }
  }
}
```

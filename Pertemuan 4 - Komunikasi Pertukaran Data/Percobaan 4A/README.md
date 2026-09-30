## Detail Percobaan
Percobaan 4A berfokus pada proses penerimaan perintah dari MQTT broker ke ESP8266 untuk mengendalikan aktuator secara langsung. ESP8266 terlebih dahulu dihubungkan ke jaringan WiFi menggunakan SSID dan password yang telah ditentukan. Setelah berhasil terhubung, ESP8266 membuat koneksi ke MQTT broker `broker.hivemq.com` menggunakan port `1883`. Program menggunakan library `PubSubClient` untuk komunikasi MQTT dan `ArduinoJson` untuk membaca data dalam format JSON. ESP8266 melakukan subscribe pada topic `unsoed/tk245004/viodupan/perintah`. Ketika pesan diterima, fungsi `callback()` membaca payload, mengubahnya menjadi `String`, kemudian melakukan deserialisasi JSON menggunakan `deserializeJson()`. Nilai `perintah` dari JSON digunakan untuk mengendalikan LED pada GPIO5, yaitu perintah `"ON"` digunakan untuk menyalakan LED dan `"OFF"` digunakan untuk mematikannya. Jika JSON yang diterima tidak valid, program menampilkan pesan kegagalan parsing pada Serial Monitor dan menghentikan proses callback.

## Penjelasan Code
Program dimulai dengan memanggil library `ESP8266WiFi` untuk menghubungkan ESP8266 ke jaringan WiFi, `PubSubClient` untuk melakukan komunikasi MQTT, dan `ArduinoJson` untuk membaca data dalam format JSON. Variabel SSID dan password digunakan sebagai konfigurasi jaringan, sedangkan `mqttServer` dan `mqttPort` menentukan alamat serta port MQTT broker. Variabel `topicPerintah` digunakan untuk menentukan topic yang akan di-subscribe, sedangkan `ledPin` menentukan GPIO5 sebagai pin LED. Objek `WiFiClient` digunakan sebagai koneksi jaringan dan `PubSubClient` digunakan sebagai MQTT client. Fungsi `callback()` membaca payload MQTT, menampilkan topic dan pesan pada Serial Monitor, kemudian melakukan parsing JSON menggunakan `deserializeJson()`. Setelah berhasil, nilai `perintah` diambil dari JSON dan dibandingkan untuk menentukan kondisi LED. Fungsi `hubungkanWiFi()` digunakan untuk menghubungkan ESP8266 ke WiFi, sedangkan `hubungkanMQTT()` digunakan untuk membuat koneksi ke broker dan melakukan subscribe pada topic perintah. Pada `setup()`, komunikasi Serial, pin LED, koneksi WiFi, MQTT broker, dan callback dikonfigurasi. Pada `loop()`, program memeriksa koneksi MQTT dan menjalankan `client.loop()` secara terus-menerus agar pesan MQTT dapat diproses dan koneksi tetap terjaga.

## Penjelasan Setiap Fungsi
- `setup()`\
Fungsi `setup()` dijalankan satu kali ketika ESP8266 pertama kali dinyalakan atau di-reset. Fungsi ini digunakan untuk memulai komunikasi Serial, mengatur pin LED, menghubungkan ESP8266 ke WiFi, mengatur MQTT broker, mendaftarkan callback, dan menghubungkan ESP8266 ke MQTT broker.

- `loop()`\
Fungsi `loop()` dijalankan secara berulang selama ESP8266 aktif. Fungsi ini digunakan untuk memeriksa koneksi MQTT dan menjalankan `client.loop()` agar pesan MQTT yang masuk dapat diproses.

- `callback()`\
Fungsi `callback()` dipanggil ketika ESP8266 menerima pesan dari topic MQTT yang telah di-subscribe. Fungsi ini membaca payload, melakukan parsing JSON, mengambil nilai `perintah`, dan mengatur kondisi LED berdasarkan perintah yang diterima. PubSubClient menggunakan callback untuk menangani pesan yang masuk dari subscription.

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
Fungsi `client.loop()` digunakan untuk memproses pesan MQTT yang masuk sekaligus menjaga koneksi MQTT tetap aktif. Fungsi ini perlu dipanggil secara berkala selama program berjalan.

- `deserializeJson()`
Fungsi `deserializeJson()` digunakan untuk mengubah teks JSON yang diterima menjadi data yang dapat diproses oleh program.

- `digitalWrite()`
Fungsi `digitalWrite()` digunakan untuk memberikan kondisi `HIGH` atau `LOW` pada pin digital. Pada program ini digunakan untuk menyalakan dan mematikan LED.

- `delay()`\
Fungsi `delay()` digunakan untuk memberikan jeda waktu pada program, terutama ketika menunggu koneksi WiFi atau mencoba kembali koneksi MQTT.

- `Serial.print()`
Fungsi `Serial.print()` digunakan untuk menampilkan teks atau data pada Serial Monitor tanpa membuat baris baru.

- `Serial.println()`
Fungsi `Serial.println()` digunakan untuk menampilkan teks atau data pada Serial Monitor kemudian membuat baris baru.

## Penjelasan Percabangan atau Conditional
Program menggunakan beberapa percabangan `if` untuk menentukan kondisi koneksi dan perintah yang diterima. Pada fungsi `callback()`, percabangan `if (error)` digunakan untuk memeriksa hasil deserialisasi JSON. Jika terdapat error, program menampilkan pesan kegagalan parsing dan menjalankan `return` sehingga perintah tidak diproses lebih lanjut. Jika JSON berhasil diproses, program mengambil nilai `perintah` dan menggunakan percabangan `if-else` untuk membandingkannya dengan `"ON"` dan `"OFF"`. Jika perintah `"ON"`, LED dinyalakan menggunakan `digitalWrite(ledPin, HIGH)`, sedangkan jika perintah `"OFF"`, LED dimatikan menggunakan `digitalWrite(ledPin, LOW)`. Jika perintah tidak sesuai dengan kedua kondisi tersebut, program menampilkan pesan bahwa perintah tidak dikenali. Selain itu, pada fungsi `loop()` terdapat percabangan `if (!client.connected())` untuk memeriksa koneksi MQTT. Jika koneksi terputus, fungsi `hubungkanMQTT()` dijalankan kembali untuk menghubungkan ESP8266 ke broker sebelum `client.loop()` digunakan untuk memproses komunikasi MQTT.

## Library atau Dependencies
Program memerlukan library dan board package berikut:
1. **ESP8266WiFi**\
   Digunakan untuk menghubungkan ESP8266 ke jaringan WiFi.
2. **PubSubClient**\
  Digunakan untuk melakukan komunikasi MQTT antara ESP8266 dan MQTT broker, termasuk proses koneksi, subscribe, penerimaan pesan melalui callback, dan pemeliharaan koneksi menggunakan `client.loop()`.
3. **ArduinoJson**\
  Digunakan untuk membaca dan memproses data yang dikirim dalam format JSON.
4. **Board package ESP8266**\
Digunakan agar program dapat dikompilasi dan diunggah ke board ESP8266 melalui Arduino IDE.

Library utama dipanggil dalam program menggunakan:
```cpp
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
```

## Jawaban Pertanyaan Percobaan 4A
1. Gambarkan diagram alur (flowchart) proses penerimaan dan pemrosesan pesan pada fungsi callback di atas!
- <img width="722" height="812" alt="Diagram Tanpa Judul drawio" src="https://github.com/user-attachments/assets/b99dad16-14e4-48f2-ad0b-e1c9144f5bcc" />
2. Apa yang akan terjadi apabila pesan yang dipublikasikan bukan merupakan format JSON yang valid?
- Apabila pesan yang diterima bukan merupakan format JSON yang valid, proses `deserializeJson()` akan menghasilkan error parsing. Program kemudian masuk ke kondisi `if (error)` dan menampilkan pesan kegagalan pada Serial Monitor. Data tersebut tidak diproses lebih lanjut sebagai perintah untuk mengendalikan LED.
3. Jelaskan mengapa fungsi `client.subscribe()` dipanggil di dalam fungsi `hubungkanMQTT()`, bukan di dalam `setup()`!
- Fungsi `client.subscribe()` diletakkan di dalam `hubungkanMQTT()` karena fungsi tersebut dijalankan setiap kali ESP8266 berhasil membuat koneksi atau melakukan reconnect ke MQTT broker. Setelah koneksi MQTT terputus, status subscription dapat hilang sehingga ESP8266 perlu melakukan subscribe kembali setelah berhasil terhubung.
4. Modifikasi program agar data JSON yang diterima juga memuat nilai intensitas (misalnya `{"perintah": "ON", "intensitas": 200}`) yang digunakan untuk mengatur kecerahan LED menggunakan PWM `(analogWrite/ledcWrite)`, dan berikan penjelasan di setiap baris kode yang ditambahkan dalam bentuk README.md!

```cpp
#include <ESP8266WiFi.h>       // Library untuk menghubungkan ESP8266 ke jaringan WiFi
#include <PubSubClient.h>      // Library untuk komunikasi MQTT
#include <ArduinoJson.h>       // Library untuk membaca dan mengolah data JSON

// ==================================================
// WIFI
// ==================================================

const char* ssid = "S24";              // Nama jaringan WiFi yang akan digunakan
const char* password = "11111111";     // Password jaringan WiFi

// ==================================================
// MQTT
// ==================================================

const char* mqttServer = "broker.hivemq.com"; // Alamat MQTT broker
const int mqttPort = 1883;                    // Port MQTT tanpa enkripsi

const char* topicPerintah =
    "unsoed/tk245004/viodupan/perintah";      // Topic untuk menerima perintah

// ==================================================
// LED / AKTUATOR
// ESP8266 D1 = GPIO5
// ==================================================

const int ledPin = 5;                 // Menentukan GPIO5/D1 sebagai pin LED

// ==================================================
// MQTT CLIENT
// ==================================================

WiFiClient espClient;                  // Membuat objek koneksi jaringan TCP
PubSubClient client(espClient);        // Membuat MQTT client menggunakan koneksi WiFi

// ==================================================
// CALLBACK MQTT
// Dipanggil ketika pesan MQTT diterima
// ==================================================

void callback(char* topic, byte* payload, unsigned int length) {

  String pesan;                       // Variabel untuk menyimpan pesan MQTT dalam bentuk String

  // Mengubah payload menjadi String
  for (unsigned int i = 0; i < length; i++) {

    pesan += (char)payload[i];         // Mengambil setiap karakter dari payload dan memasukkannya ke pesan
  }

  // Menampilkan pesan mentah
  Serial.println();                   // Membuat baris kosong pada Serial Monitor
  Serial.println("===== PESAN MQTT DITERIMA =====");

  Serial.print("Topic   : ");         // Menampilkan tulisan "Topic"
  Serial.println(topic);              // Menampilkan topic MQTT yang menerima pesan

  Serial.print("Pesan   : ");         // Menampilkan tulisan "Pesan"
  Serial.println(pesan);              // Menampilkan isi pesan JSON yang diterima

  // ==================================================
  // DESERIALISASI JSON
  // ==================================================

  JsonDocument doc;                   // Membuat tempat untuk menyimpan data JSON

  DeserializationError error =
      deserializeJson(doc, pesan);    // Mengubah pesan JSON menjadi data yang dapat dibaca program


  // Mengecek apakah JSON berhasil diproses
  if (error) {

    Serial.print("Parsing : GAGAL - "); // Menampilkan informasi bahwa parsing gagal
    Serial.println(error.c_str());      // Menampilkan jenis error JSON

    return;                             // Menghentikan callback jika JSON tidak valid
  }

  // Mengambil nilai "perintah" dari JSON
  const char* perintah = doc["perintah"];

  // Contoh JSON:
  // {"perintah":"ON","intensitas":200}

  // ==================================================
  // TAMBAHAN: MENGAMBIL NILAI INTENSITAS
  // ==================================================

  int intensitas = doc["intensitas"] | 0;
  // Mengambil nilai "intensitas" dari JSON
  // Jika intensitas tidak ditemukan, nilainya otomatis menjadi 0

  // Menampilkan hasil parsing
  Serial.println("Parsing : BERHASIL");

  Serial.print("Perintah: ");
  Serial.println(perintah);            // Menampilkan perintah ON atau OFF

  Serial.print("Intensitas: ");
  Serial.println(intensitas);          // Menampilkan nilai intensitas yang diterima

  // ==================================================
  // KONTROL AKTUATOR
  // ==================================================

  // Mengecek apakah perintah yang diterima adalah "ON"
  if (String(perintah) == "ON") {

    // Mengatur kecerahan LED menggunakan PWM
    analogWrite(ledPin, intensitas);

    // Nilai intensitas menentukan tingkat kecerahan LED
    // 0   = LED mati
    // 255 = LED paling terang

    Serial.println("Aktuator: LED ON");
    // Menampilkan status LED pada Serial Monitor

  }

  // Mengecek apakah perintah yang diterima adalah "OFF"
  else if (String(perintah) == "OFF") {

    // Memberikan nilai PWM 0 sehingga LED mati
    analogWrite(ledPin, 0);

    Serial.println("Aktuator: LED OFF");
    // Menampilkan status LED pada Serial Monitor

  }

  // Jika perintah bukan ON maupun OFF
  else {

    Serial.println("Aktuator: Perintah tidak dikenali");
    // Menampilkan pesan bahwa perintah tidak sesuai
  }

  Serial.println("===============================");
  // Menampilkan garis pembatas pada Serial Monitor
}

// ==================================================
// MENGHUBUNGKAN ESP8266 KE WIFI
// ==================================================

void hubungkanWiFi() {

  WiFi.begin(ssid, password);
  // Memulai koneksi ESP8266 ke WiFi menggunakan SSID dan password

  Serial.print("Menghubungkan ke WiFi");
  // Menampilkan status proses koneksi

  while (WiFi.status() != WL_CONNECTED) {
    // Selama ESP8266 belum terhubung ke WiFi, perulangan terus dilakukan

    delay(500);
    // Menunggu selama 500 milidetik

    Serial.print(".");
    // Menampilkan titik sebagai indikator proses koneksi
  }

  Serial.println();
  Serial.println("WiFi berhasil terhubung!");
  // Menampilkan bahwa ESP8266 berhasil terhubung ke WiFi

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  // Menampilkan alamat IP yang diperoleh ESP8266
}

// ==================================================
// MENGHUBUNGKAN ESP8266 KE MQTT BROKER
// ==================================================

void hubungkanMQTT() {

  while (!client.connected()) {
    // Selama ESP8266 belum terhubung ke MQTT broker, koneksi akan dicoba kembali

    Serial.print("Menghubungkan ke broker MQTT... ");

    String clientId =
        "ESP8266Client-" +
        String(random(0xffff), HEX);
    // Membuat ID client MQTT secara acak agar tidak sama dengan client lain

    if (client.connect(clientId.c_str())) {
      // Mencoba menghubungkan ESP8266 ke MQTT broker

      Serial.println("berhasil!");

      // Subscribe ke topic perintah
      client.subscribe(topicPerintah);
      // ESP8266 mulai berlangganan topic perintah
      // Pesan yang masuk ke topic ini akan diteruskan ke callback()

      Serial.print("Subscribe ke topic: ");
      Serial.println(topicPerintah);
      // Menampilkan topic yang berhasil di-subscribe

    }

    else {

      Serial.print("gagal, rc=");
      Serial.print(client.state());
      // Menampilkan kode status apabila koneksi MQTT gagal

      Serial.println(" | mencoba lagi...");
      // Memberikan informasi bahwa koneksi akan dicoba kembali

      delay(2000);
      // Menunggu 2 detik sebelum mencoba koneksi lagi
    }
  }
}

// ==================================================
// SETUP
// ==================================================

void setup() {

  Serial.begin(115200);
  // Memulai komunikasi Serial dengan baud rate 115200

  // Mengatur LED sebagai OUTPUT
  pinMode(ledPin, OUTPUT);
  // GPIO5 digunakan sebagai keluaran untuk mengendalikan LED

  // Kondisi awal LED mati
  digitalWrite(ledPin, LOW);
  // Memberikan kondisi awal LOW agar LED mati

  // Menghubungkan ke WiFi
  hubungkanWiFi();
  // Memanggil fungsi untuk menghubungkan ESP8266 ke jaringan WiFi

  // Mengatur MQTT broker dan port
  client.setServer(mqttServer, mqttPort);
  // Menentukan alamat broker dan port MQTT yang digunakan

  // Mendaftarkan fungsi callback
  client.setCallback(callback);
  // Menentukan callback() sebagai fungsi yang dijalankan
  // ketika pesan MQTT diterima

  // Menghubungkan ke MQTT
  hubungkanMQTT();
  // Memulai koneksi ESP8266 ke MQTT broker
}

// ==================================================
// LOOP
// ==================================================

void loop() {

  // Jika MQTT terputus, hubungkan kembali
  if (!client.connected()) {
    // Mengecek apakah koneksi MQTT masih aktif

    hubungkanMQTT();
    // Jika terputus, ESP8266 mencoba menghubungkan kembali
  }

  // Memproses pesan MQTT yang masuk
  client.loop();
  // Menjaga koneksi MQTT dan memproses pesan yang diterima
}
```

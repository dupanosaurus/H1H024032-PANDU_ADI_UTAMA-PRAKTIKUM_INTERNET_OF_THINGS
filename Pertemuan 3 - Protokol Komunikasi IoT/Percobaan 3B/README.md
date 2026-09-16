## Detail Percobaan
Percobaan 3B berfokus pada proses pengiriman data dari ESP8266 ke broker menggunakan protokol MQTT. Data yang dikirim berupa suhu dan kelembaban dalam format JSON. ESP8266 terlebih dahulu dihubungkan ke jaringan WiFi menggunakan SSID dan password yang telah ditentukan. Setelah berhasil terhubung, ESP8266 membuat koneksi ke broker MQTT `broker.hivemq.com` melalui port `1883`. Program menggunakan library `PubSubClient` untuk melakukan komunikasi MQTT dan `ArduinoJson` untuk menyusun data dalam format JSON. Data suhu sebesar `28.5` dan kelembaban sebesar `65.0` dikirimkan ke topic `ardhis/esp8266/latihan`. Serial Monitor menampilkan proses koneksi WiFi, koneksi ke broker MQTT, data JSON yang dikirim, serta status keberhasilan pengiriman data.

## Penjelasan Code
Program dimulai dengan memanggil library `ESP8266WiFi` untuk mengakses fitur WiFi pada ESP8266, `PubSubClient` untuk melakukan komunikasi MQTT, dan `ArduinoJson` untuk menyusun data dalam format JSON. SSID dan password digunakan sebagai konfigurasi jaringan WiFi, sedangkan `mqttServer`, `mqttPort`, dan `mqttTopic` digunakan untuk menentukan alamat broker, port, dan topic tujuan pengiriman data. Pada fungsi `hubungkanWiFi()`, ESP8266 mencoba terhubung ke jaringan WiFi menggunakan `WiFi.begin()`. Program menunggu sampai koneksi berhasil melalui perulangan `while (WiFi.status() != WL_CONNECTED)`. Setelah terhubung, Serial Monitor menampilkan informasi keberhasilan koneksi dan IP Address ESP8266. Pada fungsi `hubungkanMQTT()`, program memeriksa koneksi MQTT dan mencoba menghubungkan ESP8266 ke broker menggunakan `client.connect()`. Jika koneksi gagal, program akan mencoba kembali setiap 2 detik. Pada fungsi `setup()`, komunikasi serial dimulai, ESP8266 dihubungkan ke WiFi, dan alamat serta port broker MQTT ditentukan menggunakan `client.setServer()`. Pada fungsi `loop()`, program memeriksa koneksi MQTT dan melakukan koneksi ulang apabila terputus. Fungsi `client.loop()` digunakan untuk menjaga komunikasi MQTT tetap berjalan. Data suhu dan kelembaban dimasukkan ke dalam objek JSON, kemudian diubah menjadi teks menggunakan `serializeJson()`. Data tersebut dikirim ke topic MQTT menggunakan `client.publish()`. Setelah pengiriman selesai, program menunggu selama 5 detik sebelum mengulangi proses.

## Penjelasan Setiap Fungsi
- `setup()`\
Fungsi `setup()` dijalankan satu kali ketika ESP8266 pertama kali dinyalakan atau di-reset. Fungsi ini digunakan untuk memulai komunikasi serial, menghubungkan ESP8266 ke jaringan WiFi, dan menentukan server MQTT yang digunakan.

- `loop()`\
Fungsi `loop()` dijalankan secara berulang selama ESP8266 aktif. Fungsi ini digunakan untuk memeriksa koneksi MQTT, menjaga komunikasi dengan broker, membuat data JSON, mengirimkan data, dan memberikan jeda sebelum pengiriman berikutnya.

- `hubungkanWiFi()`\
Fungsi `hubungkanWiFi()` digunakan untuk menghubungkan ESP8266 ke jaringan WiFi menggunakan SSID dan password yang telah ditentukan.

- `hubungkanMQTT()`\
Fungsi `hubungkanMQTT()` digunakan untuk menghubungkan ESP8266 ke broker MQTT. Jika koneksi gagal, fungsi ini akan mencoba menghubungkan kembali sampai koneksi berhasil.

- `Serial.begin()`\
Fungsi `Serial.begin()` digunakan untuk memulai komunikasi antara ESP8266 dan Serial Monitor dengan baud rate 115200.

- `WiFi.begin()`\
Fungsi `WiFi.begin()` digunakan untuk memulai proses koneksi ESP8266 ke jaringan WiFi berdasarkan SSID dan password yang telah ditentukan.

- `WiFi.status()`\
Fungsi `WiFi.status()` digunakan untuk memeriksa status koneksi WiFi pada ESP8266.

- `delay()`\
Fungsi `delay()` digunakan untuk memberikan jeda waktu pada program, seperti saat mencoba menghubungkan ke WiFi, mencoba kembali koneksi MQTT, dan sebelum pengiriman data berikutnya.

- `Serial.print()`\
Fungsi `Serial.print()` digunakan untuk menampilkan teks atau data pada Serial Monitor tanpa membuat baris baru.

- `Serial.println()`\
Fungsi `Serial.println()` digunakan untuk menampilkan teks atau data pada Serial Monitor dan membuat baris baru setelah data ditampilkan.

- `WiFi.localIP()`\
Fungsi `WiFi.localIP()` digunakan untuk mengambil alamat IP yang diperoleh ESP8266 setelah berhasil terhubung ke jaringan WiFi.

- `client.connected()`\
Fungsi `client.connected()` digunakan untuk memeriksa apakah ESP8266 masih terhubung dengan broker MQTT.

- `client.connect()`\
Fungsi `client.connect()` digunakan untuk menghubungkan ESP8266 ke broker MQTT menggunakan client ID yang telah ditentukan.

- `client.state()`\
Fungsi `client.state()` digunakan untuk mengetahui kode status ketika koneksi ESP8266 ke broker MQTT mengalami kegagalan.

- `ESP.getChipId()`\
Fungsi `ESP.getChipId()` digunakan untuk mendapatkan Chip ID ESP8266 yang digunakan sebagai bagian dari client ID MQTT.

- `client.setServer()`\
Fungsi `client.setServer()` digunakan untuk menentukan alamat dan port broker MQTT yang akan digunakan.

- `client.loop()`\
Fungsi `client.loop()` digunakan untuk menjaga koneksi MQTT tetap aktif dan memproses komunikasi antara ESP8266 dengan broker MQTT.

- `serializeJson()`\
Fungsi `serializeJson()` digunakan untuk mengubah data JSON menjadi bentuk teks yang dapat dikirim melalui jaringan.

- `client.publish()`\
Fungsi `client.publish()` digunakan untuk mengirimkan data ke topic MQTT yang telah ditentukan.

## Penjelasan Percabangan atau Conditional
Program menggunakan percabangan `if` dan `else` untuk memeriksa kondisi koneksi MQTT dan hasil pengiriman data. Kondisi `if (!client.connected())` digunakan untuk memeriksa apakah ESP8266 tidak terhubung ke broker MQTT. Jika kondisi tersebut terpenuhi, program memanggil `hubungkanMQTT()` untuk melakukan koneksi ulang. Pada fungsi tersebut, `if (client.connect(clientId.c_str()))` digunakan untuk memeriksa keberhasilan koneksi ke broker. Jika berhasil, program menampilkan pesan bahwa koneksi berhasil, sedangkan jika gagal, bagian `else` menampilkan kode error dan program mencoba kembali setelah 2 detik. Pada proses pengiriman data, `if (berhasil)` digunakan untuk memeriksa hasil dari `client.publish()`. Jika pengiriman berhasil, program menampilkan topic dan data JSON yang dikirim. Jika gagal, bagian `else` menampilkan pesan bahwa data tidak berhasil dikirim.

## Library atau Dependencies
Program memerlukan library dan board package berikut:
1. **ESP8266WiFi**\
   Digunakan untuk menghubungkan ESP8266 ke jaringan WiFi.
2. **PubSubClient**\
   Digunakan untuk melakukan komunikasi MQTT antara ESP8266 dan broker MQTT.
3. **ArduinoJson**\
   Digunakan untuk membuat dan mengubah data ke dalam format JSON.
4. **Board package ESP8266**\
   Digunakan agar program dapat dikompilasi dan diunggah ke board ESP8266 melalui Arduino IDE.

Library utama dipanggil dalam program menggunakan:
```cpp
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
```

## Jawaban Pertanyaan Percobaan 3B
1. Apa fungsi dari topic pada protokol MQTT, dan mengapa topic yang digunakan perlu dibuat unik?
- Topic pada MQTT berfungsi sebagai alamat atau jalur untuk menentukan tempat data dipublikasikan dan diterima oleh client. Topic perlu dibuat unik agar data dari beberapa perangkat tidak tercampur dan setiap perangkat dapat menggunakan jalur komunikasi yang berbeda. 
2. Jelaskan fungsi dari perintah `client.loop()` yang dipanggil pada setiap iterasi `loop()`!
- `client.loop()` berfungsi untuk menjaga komunikasi MQTT tetap berjalan dan memproses pesan atau status koneksi dari broker. Fungsi ini perlu dipanggil secara berkala agar koneksi MQTT dapat tetap dipertahankan.
3. Apa yang akan terjadi apabila koneksi ke broker MQTT terputus di tengah program berjalan?
- Apabila koneksi broker MQTT terputus, `client.connected()` akan bernilai `false`. Program kemudian menjalankan fungsi `hubungkanMQTT()` untuk mencoba menghubungkan kembali ESP8266 ke broker. Program akan terus mencoba sampai koneksi berhasil, kemudian pengiriman data dapat dilanjutkan. 

## Detail Percobaan
Percobaan 4B berfokus pada proses pertukaran data dua arah antara ESP8266 dan MQTT broker, yaitu ESP8266 mengirimkan data sensor sekaligus menerima perintah untuk mengendalikan aktuator. ESP8266 terlebih dahulu dihubungkan ke jaringan WiFi, kemudian membuat koneksi ke MQTT broker broker.hivemq.com menggunakan port 1883. Program menggunakan library PubSubClient untuk komunikasi MQTT, ArduinoJson untuk mengolah data JSON, dan DHT untuk membaca sensor DHT11. Data suhu dari DHT11 pada GPIO4 dipublish setiap 5 detik ke topic unsoed/tk245004/viodupan/data, sedangkan perintah diterima melalui topic unsoed/tk245004/viodupan/perintah. Perintah "ON" digunakan untuk menyalakan LED pada GPIO5 dan perintah "OFF" digunakan untuk mematikannya. Pengiriman data menggunakan millis() sehingga program tidak menggunakan delay() pada proses publish dan client.loop() tetap dapat berjalan untuk memproses pesan MQTT yang masuk. Pada hasil pengamatan, data suhu berhasil dipublish dan perintah ON/OFF berhasil diterima oleh subscriber serta mengubah kondisi LED sesuai perintah.

## Penjelasan Code
Program dimulai dengan memanggil library ESP8266WiFi untuk menghubungkan ESP8266 ke jaringan WiFi, PubSubClient untuk melakukan komunikasi MQTT, ArduinoJson untuk membuat dan membaca data JSON, serta DHT untuk membaca sensor DHT11. Variabel topicData digunakan sebagai topic untuk mengirim data suhu, sedangkan topicPerintah digunakan untuk menerima perintah pengendalian LED. Sensor DHT11 menggunakan GPIO4 dan LED menggunakan GPIO5. Variabel waktuTerakhirPublish digunakan untuk menyimpan waktu pengiriman data terakhir, sedangkan intervalPublish menentukan interval pengiriman setiap 5 detik. Fungsi callback() digunakan untuk menerima pesan MQTT, mengubah payload menjadi String, melakukan parsing JSON, dan mengambil nilai perintah untuk mengendalikan LED. Fungsi hubungkanWiFi() digunakan untuk menghubungkan ESP8266 ke WiFi, sedangkan hubungkanMQTT() digunakan untuk membuat koneksi ke broker dan melakukan subscribe pada topic perintah. Pada setup(), komunikasi Serial, pin LED, sensor DHT11, WiFi, MQTT broker, dan callback dikonfigurasi. Pada loop(), program memeriksa koneksi MQTT dan menjalankan client.loop(), kemudian menggunakan millis() untuk memeriksa apakah interval 5 detik telah tercapai. Jika interval terpenuhi, sensor DHT11 membaca suhu, data dimasukkan ke dalam JSON, kemudian dikirim ke MQTT broker menggunakan client.publish().

## Penjelasan Setiap Fungsi
setup()
Fungsi setup() dijalankan satu kali ketika ESP8266 pertama kali dinyalakan atau di-reset. Fungsi ini digunakan untuk memulai komunikasi Serial, mengatur pin LED, memulai sensor DHT11, menghubungkan ESP8266 ke WiFi, mengatur MQTT broker, dan mendaftarkan callback.
loop()
Fungsi loop() dijalankan secara berulang selama ESP8266 aktif. Fungsi ini digunakan untuk memeriksa koneksi MQTT, memproses pesan yang masuk, membaca sensor DHT11, membuat data JSON, dan mengirim data suhu setiap 5 detik.
callback()
Fungsi callback() dipanggil ketika ESP8266 menerima pesan dari topic MQTT yang telah di-subscribe. Fungsi ini membaca payload, melakukan parsing JSON, mengambil nilai perintah, dan mengatur kondisi LED berdasarkan perintah yang diterima.
hubungkanWiFi()
Fungsi hubungkanWiFi() digunakan untuk menghubungkan ESP8266 ke jaringan WiFi menggunakan SSID dan password yang telah ditentukan.
hubungkanMQTT()
Fungsi hubungkanMQTT() digunakan untuk membuat koneksi antara ESP8266 dan MQTT broker. Setelah berhasil terhubung, fungsi ini melakukan subscribe pada topic perintah.
Serial.begin()
Fungsi Serial.begin() digunakan untuk memulai komunikasi antara ESP8266 dan Serial Monitor. Pada program ini digunakan baud rate 115200.
WiFi.begin()
Fungsi WiFi.begin() digunakan untuk memulai proses koneksi ESP8266 ke jaringan WiFi berdasarkan SSID dan password.
WiFi.status()
Fungsi WiFi.status() digunakan untuk memeriksa status koneksi WiFi pada ESP8266.
WiFi.localIP()
Fungsi WiFi.localIP() digunakan untuk mendapatkan alamat IP ESP8266 setelah berhasil terhubung ke WiFi.
client.setServer()
Fungsi client.setServer() digunakan untuk menentukan alamat dan port MQTT broker yang digunakan oleh MQTT client.
client.setCallback()
Fungsi client.setCallback() digunakan untuk mendaftarkan fungsi callback() sebagai pengolah pesan MQTT yang masuk.
client.connect()
Fungsi client.connect() digunakan untuk membuat koneksi ESP8266 dengan MQTT broker menggunakan Client ID.
client.subscribe()
Fungsi client.subscribe() digunakan untuk berlangganan pada topic MQTT tertentu agar ESP8266 dapat menerima pesan dari topic tersebut.
client.connected()
Fungsi client.connected() digunakan untuk memeriksa apakah MQTT client masih terhubung dengan broker.
client.loop()
Fungsi client.loop() digunakan untuk memproses pesan MQTT yang masuk sekaligus menjaga koneksi MQTT tetap aktif. Fungsi ini perlu dipanggil secara berkala agar komunikasi MQTT dapat berjalan dengan baik.
millis()
Fungsi millis() digunakan untuk mendapatkan waktu yang telah berlalu sejak ESP8266 mulai berjalan. Pada program ini digunakan untuk menentukan interval pengiriman data sensor setiap 5 detik tanpa menghentikan proses utama program.
dht.begin()
Fungsi dht.begin() digunakan untuk memulai sensor DHT11 sebelum sensor digunakan untuk membaca data.
dht.readTemperature()
Fungsi dht.readTemperature() digunakan untuk membaca nilai suhu dari sensor DHT11.
isnan()
Fungsi isnan() digunakan untuk memeriksa apakah hasil pembacaan suhu merupakan nilai yang tidak valid atau bukan angka.
serializeJson()
Fungsi serializeJson() digunakan untuk mengubah data pada objek JsonDocument menjadi teks JSON yang dapat dikirim melalui MQTT.
client.publish()
Fungsi client.publish() digunakan untuk mengirimkan data JSON suhu ke topic MQTT yang telah ditentukan. PubSubClient menyediakan fungsi publish() untuk mengirim payload ke topic tertentu.
deserializeJson()
Fungsi deserializeJson() digunakan untuk mengubah teks JSON yang diterima dari MQTT menjadi data yang dapat diproses oleh program.
digitalWrite()
Fungsi digitalWrite() digunakan untuk memberikan kondisi HIGH atau LOW pada pin digital. Pada program ini digunakan untuk menyalakan dan mematikan LED.
delay()
Fungsi delay() digunakan pada proses koneksi WiFi dan percobaan koneksi ulang MQTT. Pada proses publish data sensor, program menggunakan millis() sehingga tidak menggunakan delay() untuk menentukan interval pengiriman.
Serial.print()
Fungsi Serial.print() digunakan untuk menampilkan teks atau data pada Serial Monitor tanpa membuat baris baru.
Serial.println()
Fungsi Serial.println() digunakan untuk menampilkan teks atau data pada Serial Monitor kemudian membuat baris baru.

## Penjelasan Percabangan atau Conditional
Program menggunakan beberapa percabangan if untuk menentukan kondisi koneksi, pembacaan sensor, dan perintah yang diterima. Pada fungsi callback(), percabangan if (error) digunakan untuk memeriksa hasil parsing JSON dan jika terjadi error program menampilkan pesan kegagalan kemudian menjalankan return. Setelah JSON berhasil diproses, percabangan if-else digunakan untuk memeriksa nilai perintah, yaitu "ON" untuk menyalakan LED dan "OFF" untuk mematikannya, sedangkan perintah lain akan dianggap tidak dikenali. Pada fungsi loop(), percabangan if (!client.connected()) digunakan untuk memeriksa koneksi MQTT dan menjalankan hubungkanMQTT() jika koneksi terputus. Selanjutnya, percabangan if (millis() - waktuTerakhirPublish >= intervalPublish) digunakan untuk menentukan apakah sudah mencapai interval 5 detik sehingga data sensor dapat dikirim. Setelah suhu dibaca, if (isnan(suhu)) digunakan untuk memeriksa apakah pembacaan DHT11 gagal. Pada proses publish, if (client.publish(topicData, buffer)) digunakan untuk memeriksa keberhasilan pengiriman data, sedangkan bagian else menampilkan pesan apabila pengiriman gagal.

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
1. 

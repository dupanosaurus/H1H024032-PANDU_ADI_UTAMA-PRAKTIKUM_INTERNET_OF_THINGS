## Detail Percobaan
Percobaan 2A berfokus pada proses menghubungkan ESP8266 ke jaringan WiFi menggunakan mode Station (STA). Program mengatur ESP8266 sebagai perangkat yang terhubung ke jaringan WiFi yang tersedia, kemudian menampilkan informasi koneksi berupa IP Address, MAC Address, dan RSSI melalui Serial Monitor. Program juga menggunakan LED sebagai indikator status koneksi WiFi. Pada percobaan ini dilakukan pengujian menggunakan SSID dan password yang benar maupun salah untuk mengetahui respons ESP8266 terhadap konfigurasi jaringan yang berbeda. Selain itu, program dimodifikasi agar ESP8266 dapat mencoba melakukan koneksi ulang ketika koneksi WiFi terputus.

## Penjelasan Code
Program dimulai dengan memanggil library `ESP8266WiFi` yang digunakan untuk mengakses fitur WiFi pada ESP8266. SSID dan password jaringan WiFi kemudian ditentukan sebagai konfigurasi koneksi. GPIO 2 digunakan sebagai pin LED indikator. Pada fungsi `setup()`, komunikasi serial dan pin LED diinisialisasi. ESP8266 kemudian diatur ke mode Station menggunakan `WiFi.mode(WIFI_STA)` dan mulai melakukan koneksi menggunakan `WiFi.begin()`. Program akan menunggu sampai status koneksi berubah menjadi `WL_CONNECTED`. Setelah berhasil terhubung, program menampilkan IP Address, MAC Address, dan nilai RSSI pada Serial Monitor serta menyalakan LED sebagai indikator koneksi berhasil. Pada fungsi `loop()`, program memeriksa status koneksi WiFi secara berkala. Jika ESP8266 masih terhubung, Serial Monitor menampilkan status "Terhubung". Jika koneksi terputus, LED dimatikan dan ESP8266 mencoba melakukan koneksi ulang menggunakan `WiFi.reconnect()`.

## Penjelasan Setiap Fungsi
- `setup()`\
Fungsi `setup()` dijalankan satu kali ketika ESP8266 pertama kali dinyalakan atau di-reset. Fungsi ini digunakan untuk memulai komunikasi serial, mengatur pin LED sebagai output, mengatur ESP8266 ke mode Station, dan memulai koneksi ke jaringan WiFi.

- `loop()`\
Fungsi `loop()` dijalankan secara berulang selama ESP8266 aktif. Pada fungsi ini, program memeriksa status koneksi WiFi. Jika masih terhubung, program menampilkan status koneksi. Jika koneksi terputus, LED dimatikan dan program mencoba melakukan koneksi ulang.

- `WiFi.mode(WIFI_STA)`\
Fungsi ini digunakan untuk mengatur ESP8266 ke mode Station (STA), sehingga ESP8266 bertindak sebagai klien yang terhubung ke jaringan WiFi yang sudah tersedia.

- `WiFi.begin(ssid, password)`\
Fungsi ini digunakan untuk memulai proses koneksi ESP8266 ke jaringan WiFi menggunakan SSID dan password yang telah ditentukan.

- `WiFi.status()`\
Fungsi ini digunakan untuk mengetahui status koneksi WiFi pada ESP8266. Status `WL_CONNECTED` menunjukkan bahwa ESP8266 berhasil terhubung ke jaringan WiFi.

- `WiFi.localIP()`\
Fungsi ini digunakan untuk mendapatkan IP Address yang diberikan kepada ESP8266 setelah berhasil terhubung ke jaringan WiFi.

- `WiFi.macAddress()`\
Fungsi ini digunakan untuk mendapatkan MAC Address dari perangkat ESP8266.

- `WiFi.RSSI()`\
Fungsi ini digunakan untuk membaca kekuatan sinyal WiFi yang diterima ESP8266 dalam satuan dBm.

- `WiFi.reconnect()`\
Fungsi ini digunakan untuk memerintahkan ESP8266 agar mencoba menghubungkan kembali ke jaringan WiFi ketika koneksi terputus.

- `digitalWrite()`\
Fungsi ini digunakan untuk mengatur kondisi LED indikator. LED dinyalakan ketika ESP8266 berhasil terhubung dan dimatikan ketika koneksi terputus.

## Penjelasan Percabangan atau Conditional
Program menggunakan percabangan `if-else` untuk memeriksa kondisi koneksi WiFi. Kondisi `if (WiFi.status() == WL_CONNECTED)` akan bernilai benar apabila ESP8266 masih terhubung ke jaringan WiFi. Program kemudian menampilkan pesan "Status: Terhubung". Jika kondisi tersebut bernilai salah, bagian `else` akan dijalankan. Program menampilkan pesan "Status: Terputus", mematikan LED, kemudian menjalankan `WiFi.reconnect()` untuk mencoba menghubungkan kembali ESP8266 ke jaringan WiFi.

## Library atau Dependencies
Program memerlukan library berikut:
1. ESP8266WiFi, yang digunakan untuk mengatur dan menggunakan fitur jaringan WiFi pada ESP8266.
2. Board package ESP8266, agar program dapat dikompilasi dan diunggah ke perangkat ESP8266.

Library utama dipanggil dalam program menggunakan: `#include <ESP8266WiFi.h>`

## Jawaban Pertanyaan Percobaan 2A
1. Gambarkan diagram alur (flowchart) proses koneksi ESP8266 ke jaringan WiFi pada program di atas!
- <img width="472" height="692" alt="Diagram Tanpa Judul drawio" src="https://github.com/user-attachments/assets/ca5ca850-98f2-4aa3-8051-9d4bd642f214" />
2. Apa fungsi dari perintah `WiFi.mode(WIFI_STA)` pada program tersebut?
- Perintah `WiFi.mode(WIFI_STA)` berfungsi untuk mengatur ESP8266 ke mode Station (STA), sehingga ESP8266 bertindak sebagai klien yang terhubung ke jaringan WiFi yang sudah tersedia.
3. Jelaskan apa yang terjadi apabila SSID atau password yang dimasukkan salah!
- Jika SSID atau password yang dimasukkan salah, ESP8266 tidak dapat terhubung ke jaringan WiFi. Status koneksi tidak mencapai `WL_CONNECTED`, sehingga program akan terus menunggu proses koneksi. Pada Serial Monitor akan terlihat titik-titik yang terus muncul sebagai tanda bahwa ESP8266 masih mencoba melakukan koneksi. Pada pengujian menggunakan konfigurasi yang salah, ESP8266 tidak berhasil terhubung dan LED tetap dalam kondisi mati.
4. Modifikasi program agar ESP8266 mencoba menghubungkan ulang (reconnect) secara otomatis apabila koneksi WiFi terputus, dan berikan penjelasan di setiap baris kode yang ditambahkan dalam bentuk README.md!

```cpp
#include <ESP8266WiFi.h> // Memanggil library WiFi untuk menggunakan fitur WiFi pada ESP8266

const char* ssid = "Authentic Nasgor Tuna Asap"; // Menentukan nama jaringan WiFi yang akan digunakan
const char* password = "12345678"; // Menentukan password jaringan WiFi yang akan digunakan

const int ledPin = 2; // Menentukan GPIO 2 sebagai pin LED indikator pada ESP8266

void setup() {
  Serial.begin(115200); // Memulai komunikasi serial dengan baud rate 115200

  pinMode(ledPin, OUTPUT); // Mengatur pin LED sebagai pin output
  digitalWrite(ledPin, LOW); // Mematikan LED saat sistem pertama kali dijalankan

  WiFi.mode(WIFI_STA); // Mengatur ESP8266 sebagai Station yang terhubung ke jaringan WiFi
  WiFi.begin(ssid, password); // Memulai proses koneksi ESP8266 ke jaringan WiFi

  Serial.print("Menghubungkan ke WiFi"); // Menampilkan informasi bahwa ESP8266 sedang mencoba terhubung ke WiFi

  while (WiFi.status() != WL_CONNECTED) { // Menunggu sampai ESP8266 berhasil terhubung ke WiFi
    delay(500); // Memberikan jeda selama 500 milidetik sebelum pengecekan berikutnya
    Serial.print("."); // Menampilkan titik sebagai indikator proses koneksi
  }

  Serial.println(); // Membuat baris baru pada Serial Monitor
  Serial.println("WiFi berhasil terhubung!"); // Menampilkan informasi bahwa koneksi WiFi berhasil

  Serial.print("IP Address : "); // Menampilkan teks IP Address
  Serial.println(WiFi.localIP()); // Menampilkan alamat IP yang diperoleh ESP8266

  Serial.print("MAC Address : "); // Menampilkan teks MAC Address
  Serial.println(WiFi.macAddress()); // Menampilkan alamat MAC ESP8266

  Serial.print("RSSI (dBm) : "); // Menampilkan teks RSSI
  Serial.println(WiFi.RSSI()); // Menampilkan kekuatan sinyal WiFi dalam satuan dBm

  digitalWrite(ledPin, HIGH); // Menyalakan LED sebagai indikator WiFi berhasil terhubung
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) { // Memeriksa apakah ESP8266 masih terhubung ke WiFi
    Serial.println("Status: Terhubung"); // Menampilkan status bahwa ESP8266 masih terhubung
  } else {
    Serial.println("Status: Terputus"); // Menampilkan status bahwa koneksi WiFi terputus
    digitalWrite(ledPin, LOW); // Mematikan LED ketika koneksi WiFi terputus

    Serial.println("Mencoba reconnect..."); // Menampilkan informasi bahwa ESP8266 akan mencoba menghubungkan ulang
    WiFi.reconnect(); // Memerintahkan ESP8266 untuk mencoba menghubungkan kembali ke WiFi
    delay(5000); // Memberikan waktu 5 detik untuk proses reconnect
  }

  delay(5000); // Memberikan jeda selama 5 detik sebelum melakukan pengecekan kembali
}
```

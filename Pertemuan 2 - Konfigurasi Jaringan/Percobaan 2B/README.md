## Detail Percobaan
Percobaan 2B berfokus pada proses membuat ESP8266 menjadi Access Point (AP) atau jaringan WiFi sendiri. Program mengatur ESP8266 ke mode Access Point menggunakan `WiFi.mode(WIFI_AP)`, kemudian membuat jaringan WiFi dengan SSID dan password yang telah ditentukan. Pada percobaan ini, ESP8266 membuat jaringan dengan SSID `ESPTunaAsap` dan password `12345678`. Setelah Access Point aktif, program menampilkan IP Address AP melalui Serial Monitor dan menghitung jumlah perangkat yang terhubung ke jaringan tersebut secara berkala.

## Penjelasan Code
Program dimulai dengan memanggil library `ESP8266WiFi` yang digunakan untuk mengakses fitur WiFi pada ESP8266. SSID dan password Access Point kemudian ditentukan pada variabel `ap_ssid` dan `ap_password`. Pada fungsi `setup()`, komunikasi serial dimulai dan ESP8266 diatur ke mode Access Point menggunakan `WiFi.mode(WIFI_AP)`. Setelah itu, fungsi `WiFi.softAP()` digunakan untuk membuat jaringan WiFi dengan SSID dan password yang telah ditentukan. Program kemudian mengambil IP Address Access Point menggunakan `WiFi.softAPIP()` dan menampilkan informasi jaringan melalui Serial Monitor. Pada fungsi `loop()`, program menghitung jumlah perangkat yang sedang terhubung ke Access Point menggunakan `WiFi.softAPgetStationNum()`. Jumlah perangkat kemudian ditampilkan pada Serial Monitor setiap lima detik.

## Penjelasan Setiap Fungsi
- `setup()`\
Fungsi `setup()` dijalankan satu kali ketika ESP8266 pertama kali dinyalakan atau di-reset. Fungsi ini digunakan untuk memulai komunikasi serial, mengatur ESP8266 ke mode Access Point, membuat jaringan WiFi, dan menampilkan informasi jaringan.

- `loop()`\
Fungsi `loop()` dijalankan secara berulang selama ESP8266 aktif. Pada fungsi ini, program menghitung jumlah perangkat yang terhubung ke Access Point dan menampilkannya melalui Serial Monitor.

- `WiFi.mode(WIFI_AP)`\
Fungsi ini digunakan untuk mengatur ESP8266 ke mode Access Point (AP), sehingga ESP8266 dapat membuat dan menyediakan jaringan WiFi sendiri.

- `WiFi.softAP(ap_ssid, ap_password)`\
Fungsi ini digunakan untuk membuat Access Point menggunakan SSID dan password yang telah ditentukan.

- `WiFi.softAPIP()`\
Fungsi ini digunakan untuk mendapatkan IP Address dari Access Point yang dibuat oleh ESP8266.

- `WiFi.softAPgetStationNum()`\
Fungsi ini digunakan untuk mengetahui jumlah perangkat atau client yang sedang terhubung ke Access Point ESP8266.

- `Serial.begin()`\
Fungsi ini digunakan untuk memulai komunikasi antara ESP8266 dengan Serial Monitor menggunakan baud rate yang ditentukan.

- `Serial.print()`\
Fungsi ini digunakan untuk menampilkan teks pada Serial Monitor tanpa berpindah ke baris baru.

- `Serial.println()`\
Fungsi ini digunakan untuk menampilkan teks atau data pada Serial Monitor dan kemudian berpindah ke baris berikutnya.

- `delay()`\
Fungsi ini digunakan untuk memberikan jeda waktu sebelum program menjalankan proses berikutnya.

## Penjelasan Percabangan atau Conditional
Program pada Percobaan 2B tidak menggunakan percabangan `if-else`. Program hanya menjalankan proses secara berurutan pada fungsi `setup()` dan melakukan pengulangan pada fungsi `loop()`. Pada fungsi `loop()`, jumlah perangkat yang terhubung ke Access Point diperiksa menggunakan `WiFi.softAPgetStationNum()`. Nilai jumlah perangkat kemudian langsung ditampilkan melalui Serial Monitor.

## Library atau Dependencies
Program memerlukan library berikut:
1. ESP8266WiFi, yang digunakan untuk membuat dan mengatur jaringan WiFi pada ESP8266.
2. Board package ESP8266, agar program dapat dikompilasi dan diunggah ke perangkat ESP8266.

Library utama dipanggil dalam program menggunakan: `#include <ESP8266WiFi.h>`

## Jawaban Pertanyaan Percobaan 2B
1. Apa fungsi dari IP `192.168.4.1` pada mode Access Point ESP8266?
- IP `192.168.4.1` merupakan IP Address yang digunakan oleh Access Point ESP8266. Alamat tersebut digunakan sebagai alamat jaringan lokal sehingga perangkat yang terhubung ke Access Point dapat berkomunikasi melalui jaringan yang dibuat oleh ESP8266.
2. Jelaskan perbedaan mode Station (STA) dan Access Point (AP) pada ESP8266!
- Pada mode Station (STA), ESP8266 bertindak sebagai client yang terhubung ke jaringan WiFi yang sudah tersedia. ESP8266 akan memperoleh IP Address dari jaringan tersebut.
- Pada mode Access Point (AP), ESP8266 bertindak sebagai penyedia jaringan WiFi dan membuat jaringan sendiri yang dapat ditemukan serta digunakan oleh perangkat lain.
3. Apa risiko keamanan jika Access Point dibuat tanpa password?
- Jika Access Point dibuat tanpa password, perangkat lain yang berada dalam jangkauan jaringan dapat terhubung dengan mudah. Hal tersebut dapat menyebabkan akses ke jaringan lokal menjadi tidak terbatas dan meningkatkan risiko penggunaan jaringan oleh perangkat yang tidak diizinkan. Oleh karena itu, penggunaan password diperlukan untuk membatasi perangkat yang dapat terhubung.
4. Modifikasi program agar ESP8266 dapat bekerja dalam mode AP + STA secara bersamaan, dan berikan penjelasan di setiap baris kode yang ditambahkan dalam bentuk README.md!

```cpp
#include <ESP8266WiFi.h> // Memanggil library WiFi untuk menggunakan fitur jaringan pada ESP8266

const char* sta_ssid = "Authentic Nasgor Tuna Asap"; // Menentukan nama WiFi rumah yang akan digunakan sebagai Station
const char* sta_password = "12345678"; // Menentukan password WiFi rumah

const char* ap_ssid = "ESPTunaAsap"; // Menentukan nama jaringan WiFi yang dibuat ESP8266 sebagai Access Point
const char* ap_password = "12345678"; // Menentukan password Access Point dengan minimal 8 karakter

void setup() { // Fungsi setup() dijalankan satu kali saat ESP8266 dinyalakan
  Serial.begin(115200); // Memulai komunikasi serial dengan baud rate 115200

  WiFi.mode(WIFI_AP_STA); // Mengatur ESP8266 agar bekerja sebagai Access Point dan Station secara bersamaan

  WiFi.begin(sta_ssid, sta_password); // Memulai proses koneksi ESP8266 ke WiFi rumah sebagai Station
  WiFi.softAP(ap_ssid, ap_password); // Membuat Access Point menggunakan SSID dan password yang telah ditentukan

  IPAddress apIP = WiFi.softAPIP(); // Mengambil alamat IP dari Access Point ESP8266

  Serial.println("AP + STA aktif!"); // Menampilkan informasi bahwa mode AP dan Station telah aktif

  Serial.print("STA SSID : "); // Menampilkan keterangan nama WiFi Station
  Serial.println(sta_ssid); // Menampilkan nama WiFi rumah yang digunakan

  Serial.print("STA IP Address : "); // Menampilkan keterangan alamat IP Station
  Serial.println(WiFi.localIP()); // Menampilkan alamat IP ESP8266 dari WiFi rumah

  Serial.print("AP SSID : "); // Menampilkan keterangan nama Access Point
  Serial.println(ap_ssid); // Menampilkan nama Access Point yang dibuat ESP8266

  Serial.print("AP IP Address : "); // Menampilkan keterangan alamat IP Access Point
  Serial.println(apIP); // Menampilkan alamat IP Access Point ESP8266
}

void loop() { // Fungsi loop() dijalankan secara berulang
  int jumlahClient = WiFi.softAPgetStationNum(); // Menghitung jumlah perangkat yang sedang terhubung ke Access Point

  Serial.print("Jumlah perangkat terhubung ke AP: "); // Menampilkan keterangan jumlah perangkat yang terhubung
  Serial.println(jumlahClient); // Menampilkan jumlah perangkat yang terhubung ke Access Point

  if (WiFi.status() == WL_CONNECTED) { // Memeriksa apakah ESP8266 masih terhubung ke WiFi rumah
    Serial.println("Status STA: Terhubung"); // Menampilkan status koneksi Station
  } else {
    Serial.println("Status STA: Terputus"); // Menampilkan status jika koneksi Station terputus
  }

  delay(5000); // Memberikan jeda selama 5 detik sebelum melakukan pengecekan kembali
}
```

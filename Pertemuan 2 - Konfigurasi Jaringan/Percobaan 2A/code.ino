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
  }

  delay(5000); // Memberikan jeda selama 5 detik sebelum melakukan pengecekan kembali
}


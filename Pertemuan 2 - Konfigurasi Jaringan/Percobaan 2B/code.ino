#include <ESP8266WiFi.h> // Memanggil library WiFi untuk menggunakan fitur jaringan pada ESP8266

const char* ap_ssid = "ESPTunaAsap"; // Menentukan nama jaringan WiFi (SSID) yang dibuat ESP8266
const char* ap_password = "12345678"; // Menentukan password Access Point dengan minimal 8 karakter

void setup() { // Fungsi setup() dijalankan satu kali saat ESP8266 dinyalakan
  Serial.begin(115200); // Memulai komunikasi serial dengan baud rate 115200

  WiFi.mode(WIFI_AP); // Mengatur ESP8266 ke mode Access Point
  WiFi.softAP(ap_ssid, ap_password); // Membuat Access Point menggunakan SSID dan password yang telah ditentukan

  IPAddress apIP = WiFi.softAPIP(); // Mengambil alamat IP dari Access Point ESP8266

  Serial.println("Access Point aktif!"); // Menampilkan informasi bahwa Access Point telah aktif
  Serial.print("SSID : "); // Menampilkan keterangan SSID
  Serial.println(ap_ssid); // Menampilkan nama SSID Access Point
  Serial.print("IP Address : "); // Menampilkan keterangan alamat IP
  Serial.println(apIP); // Menampilkan alamat IP Access Point
}

void loop() { // Fungsi loop() dijalankan berulang kali
  int jumlahClient = WiFi.softAPgetStationNum(); // Menghitung jumlah perangkat yang sedang terhubung ke Access Point
  Serial.print("Jumlah perangkat terhubung: "); // Menampilkan keterangan jumlah perangkat
  Serial.println(jumlahClient); // Menampilkan jumlah perangkat yang terhubung
  delay(5000); // Memberikan jeda selama 5 detik sebelum melakukan pengecekan kembali
}


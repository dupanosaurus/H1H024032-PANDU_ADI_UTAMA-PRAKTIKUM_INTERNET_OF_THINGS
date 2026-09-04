#include <DHT.h> // Memanggil library DHT untuk menggunakan sensor DHT11

#define DHTPIN 4       // Menentukan GPIO 4 atau D2 sebagai pin DATA sensor DHT11
#define DHTTYPE DHT11  // Menentukan jenis sensor DHT yang digunakan, yaitu DHT11

#define RELAYPIN 5     // Menentukan GPIO 5 atau D1 sebagai pin input relay

DHT dht(DHTPIN, DHTTYPE); // Membuat objek DHT dengan pin dan jenis sensor yang telah ditentukan

const float suhuThreshold = 30.0; // Menentukan batas suhu sebesar 30°C untuk mengendalikan relay

void setup() {
  Serial.begin(115200); // Memulai komunikasi serial dengan baud rate 115200

  dht.begin(); // Menginisialisasi sensor DHT11

  pinMode(RELAYPIN, OUTPUT); // Mengatur pin relay sebagai pin output

  // Relay mati saat awal
  digitalWrite(RELAYPIN, LOW); // Mengatur relay dalam kondisi mati saat sistem pertama kali dijalankan

  Serial.println("Sistem DHT11 + Relay"); // Menampilkan informasi sistem pada Serial Monitor
  Serial.println("Menunggu pembacaan sensor..."); // Menampilkan informasi bahwa sistem sedang menunggu pembacaan sensor
}

void loop() {

  // Membaca suhu
  float suhu = dht.readTemperature(); // Membaca nilai suhu dari sensor DHT11

  // Periksa apakah pembacaan berhasil
  if (isnan(suhu)) { // Memeriksa apakah nilai suhu yang dibaca tidak valid

    Serial.println("Gagal membaca data sensor!"); // Menampilkan pesan apabila pembacaan sensor gagal

  } else { // Menjalankan program jika data suhu berhasil dibaca

    Serial.print("Suhu: "); // Menampilkan teks suhu pada Serial Monitor
    Serial.print(suhu); // Menampilkan nilai suhu yang terbaca
    Serial.print(" °C -> "); // Menampilkan satuan suhu dan tanda pemisah

    // Jika suhu lebih dari 30°C
    if (suhu > suhuThreshold) { // Memeriksa apakah suhu melebihi batas yang telah ditentukan

      digitalWrite(RELAYPIN, HIGH); // Mengaktifkan relay
      Serial.println("Aktuator: ON"); // Menampilkan status aktuator menyala

    } else { // Menjalankan program jika suhu tidak melebihi batas

      digitalWrite(RELAYPIN, LOW); // Menonaktifkan relay
      Serial.println("Aktuator: OFF"); // Menampilkan status aktuator mati
    }
  }

  delay(2000); // Memberikan jeda selama 2 detik sebelum pembacaan suhu berikutnya
}

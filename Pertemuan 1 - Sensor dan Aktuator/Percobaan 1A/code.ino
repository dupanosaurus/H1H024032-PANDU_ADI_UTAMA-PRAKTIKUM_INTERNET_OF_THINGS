#include <DHT.h> // Memanggil library DHT untuk menggunakan sensor DHT11

#define DHTPIN 4 // Menentukan pin GPIO 4 sebagai pin data sensor DHT11
#define DHTTYPE DHT11 // Menentukan jenis sensor DHT yang digunakan, yaitu DHT11

DHT dht(DHTPIN, DHTTYPE); // Membuat objek sensor DHT dengan pin dan jenis sensor yang telah ditentukan

void setup() {
  Serial.begin(115200); // Memulai komunikasi serial dengan baud rate 115200
  delay(1000); // Memberikan jeda selama 1 detik

  Serial.println(); // Membuat baris kosong pada Serial Monitor
  Serial.println("Memulai DHT11..."); // Menampilkan informasi bahwa sensor DHT11 akan digunakan

  dht.begin(); // Menginisialisasi sensor DHT11
  delay(2000); // Memberikan jeda selama 2 detik setelah inisialisasi sensor
}

void loop() {
  float kelembaban = dht.readHumidity(); // Membaca nilai kelembaban dari sensor DHT11
  float suhu = dht.readTemperature(); // Membaca nilai suhu dari sensor DHT11

  if (isnan(kelembaban) || isnan(suhu)) { // Memeriksa apakah data kelembaban atau suhu tidak valid
    Serial.println("Gagal membaca data dari sensor DHT11!"); // Menampilkan pesan jika pembacaan sensor gagal
  } else { // Menjalankan program jika data sensor berhasil dibaca
    Serial.print("Suhu: "); // Menampilkan teks suhu pada Serial Monitor
    Serial.print(suhu); // Menampilkan nilai suhu yang terbaca
    Serial.print(" °C | Kelembaban: "); // Menampilkan satuan suhu dan teks kelembaban
    Serial.print(kelembaban); // Menampilkan nilai kelembaban yang terbaca
    Serial.println(" %"); // Menampilkan satuan persen dan berpindah ke baris berikutnya
  }

  delay(3000); // Memberikan jeda selama 3 detik sebelum pembacaan berikutnya
}

## Detail Percobaan
Percobaan 5A membahas pengolahan data suhu pada perangkat menggunakan filter *moving average* dan pencatatan suhu minimum serta maksimum. Pada kode yang digunakan, pembacaan sensor DHT22 digantikan oleh fungsi `bacaSuhuMock()` yang menghasilkan suhu simulasi, menambahkan *noise* kecil, dan memberikan lonjakan suhu setiap 25 pembacaan. Nilai suhu mentah diproses menggunakan rata-rata bergerak dari maksimal lima sampel terakhir. Program kemudian menampilkan suhu mentah, hasil *moving average*, suhu minimum, dan suhu maksimum pada Serial Monitor setiap dua detik.

## Penjelasan Code
Program diawali dengan `#include <Arduino.h>` untuk menggunakan fungsi dasar Arduino. Konstanta `N` bernilai 5 sebagai jumlah maksimum sampel *moving average*, sedangkan `buffer[N]` menyimpan sampel suhu. Variabel `indeks` menunjukkan posisi penulisan data berikutnya dan `jumlah` mencatat banyak sampel yang sudah masuk ke buffer. Variabel `suhuMin` dan `suhuMax` diberi nilai awal yang sangat besar dan sangat kecil agar data pertama dapat memperbarui nilai minimum dan maksimum. Fungsi `bacaSuhuMock()` menghasilkan suhu simulasi dari suhu dasar yang berubah secara bertahap, ditambah *noise* acak. Setiap pembacaan kelipatan 25, suhu ditambah 8 °C untuk mensimulasikan lonjakan. Fungsi `hitungMovingAverage()` menyimpan nilai baru ke buffer, memperbarui indeks secara melingkar, lalu menghitung rata-rata sampel yang tersedia. Pada `setup()`, program memulai komunikasi Serial, menginisialisasi angka acak, dan menampilkan judul percobaan. Pada `loop()`, program mengambil suhu simulasi, menghitung *moving average*, memperbarui nilai minimum dan maksimum, menampilkan seluruh nilai ke Serial Monitor, lalu menunggu dua detik sebelum mengulang proses.

## Penjelasan Setiap Fungsi
- `bacaSuhuMock()`\
Menghasilkan data suhu simulasi sebagai pengganti pembacaan sensor DHT22. Variabel `jumlahBaca` menghitung jumlah pemanggilan fungsi. Suhu dasar dihitung menggunakan fungsi `sin()`, kemudian ditambahkan *noise* dari `random(-5, 6) * 0.1`. Setiap pembacaan kelipatan 25, suhu ditambah 8 °C. Fungsi mengembalikan nilai suhu melalui `return suhu`.

- `hitungMovingAverage(float nilaiBaru)`\
Memasukkan suhu terbaru ke `buffer[indeks]`, lalu memajukan posisi indeks menggunakan `(indeks + 1) % N`. Jika jumlah sampel belum mencapai lima, nilai `jumlah` ditambah satu. Selanjutnya, perulangan `for` menjumlahkan seluruh sampel yang tersedia dan fungsi mengembalikan hasil pembagian total dengan jumlah sampel.

- `setup()`\
Dijalankan satu kali saat board mulai menyala atau di-reset. Fungsi ini memulai komunikasi Serial dengan baud rate 115200, menginisialisasi generator angka acak menggunakan `randomSeed(analogRead(0))`, dan menampilkan judul Percobaan 5A pada Serial Monitor.

- `loop()`\
Dijalankan berulang kali selama board aktif. Fungsi ini mengambil suhu dari `bacaSuhuMock()`, menghitung hasil filter melalui `hitungMovingAverage()`, memperbarui suhu minimum dan maksimum, menampilkan hasil pengolahan ke Serial Monitor, lalu memberikan jeda dua detik menggunakan `delay(2000)`.

- `Serial.begin()`\
Memulai komunikasi Serial antara board dan Serial Monitor. Pada program ini, baud rate yang digunakan adalah 115200.

- `randomSeed()`\
Menginisialisasi generator angka pseudoacak agar hasil dari fungsi `random()` tidak selalu dimulai dari urutan yang sama.

- `analogRead()`\
Membaca nilai masukan analog yang digunakan sebagai nilai awal (*seed*) untuk generator angka acak pada `randomSeed(analogRead(0))`.

- `sin()`\
Menghitung fungsi sinus yang digunakan untuk membuat suhu dasar berubah secara bertahap.

- `random()`\
Menghasilkan angka pseudoacak. Dalam kode ini, `random(-5, 6)` menghasilkan nilai dari -5 sampai 5 yang kemudian dikalikan 0,1 sebagai *noise* kecil.

- `return`\
Mengembalikan nilai dari fungsi kepada bagian program yang memanggilnya, seperti nilai suhu dari `bacaSuhuMock()` dan nilai rata-rata dari `hitungMovingAverage()`.

- `Serial.print()`\
Menampilkan teks atau nilai pada Serial Monitor tanpa berpindah ke baris baru.

- `Serial.println()`\
Menampilkan teks atau nilai pada Serial Monitor kemudian berpindah ke baris baru.

- `delay()`\
Memberikan jeda selama waktu yang ditentukan. Pada program ini, `delay(2000)` memberi jeda dua detik di antara pengambilan data.

## Penjelasan Percabangan atau Conditional
Program menggunakan percabangan `if` pada fungsi `bacaSuhuMock()` untuk memeriksa apakah `jumlahBaca % 25 == 0`. Jika kondisi tersebut benar, suhu ditambah 8 °C sebagai simulasi lonjakan. Pada fungsi `hitungMovingAverage()`, kondisi `if (jumlah < N)` memastikan jumlah sampel tidak melebihi kapasitas buffer. Di dalam `loop()`, kondisi `if (suhu < suhuMin)` memperbarui suhu minimum ketika suhu baru lebih rendah daripada nilai sebelumnya, sedangkan `if (suhu > suhuMax)` memperbarui suhu maksimum ketika suhu baru lebih tinggi. Program juga menggunakan perulangan `for` untuk menjumlahkan sampel yang tersimpan di buffer.

## Library atau Dependencies
Program menggunakan komponen berikut:
1. **Arduino core (`Arduino.h`)**\
Menyediakan fungsi dasar yang digunakan program, termasuk komunikasi Serial, `delay()`, pembacaan analog, dan fungsi angka pseudoacak.
2. **Fungsi matematika (`sin()`)**\
Digunakan untuk menghasilkan perubahan suhu dasar pada fungsi `bacaSuhuMock()`. Fungsi matematika ini tersedia melalui lingkungan Arduino yang digunakan.
3. **Board package ESP32**\
Diperlukan agar program dapat dikompilasi dan diunggah ke board ESP32 melalui Arduino IDE.

Library utama dipanggil dalam program menggunakan:
```cpp
#include <Arduino.h>
```
Program ini tidak menggunakan library DHT karena fungsi `bacaSuhuMock()` menjadi pengganti sensor DHT22 sesuai keterangan pada buku catatan praktikum. Oleh karena itu, nilai yang ditampilkan merupakan data simulasi, bukan hasil pengukuran langsung dari sensor.

## Jawaban Pertanyaan Percobaan 5A
1.Gambarkan diagram alur (flowchart) proses perhitungan moving average pada fungsi `hitungMovingAverage()`!
- <img width="442" height="822" alt="Diagram Tanpa Judul drawio" src="https://github.com/user-attachments/assets/c3ad3ef9-f19f-49a9-b928-f7c93ce8b763" />
2. Jelaskan fungsi dari operasi `(indeks + 1) % N` pada program tersebut!
- Operasi `(indeks + 1) % N` berfungsi untuk menggeser posisi penulisan data pada *circular buffer*. Operator modulus memastikan indeks tetap berada dalam batas ukuran buffer. Jika `N = 5`, indeks bergerak dari 0 hingga 4, lalu kembali ke 0. Data baru akan menimpa data lama pada posisi tersebut sehingga buffer menyimpan maksimal lima pembacaan suhu terbaru tanpa perlu menggeser seluruh isi array.
3. Apa dampaknya terhadap data hasil filter apabila nilai N diperbesar menjadi 20 atau diperkecil menjadi 2?
- Nilai `N` memengaruhi kehalusan dan kecepatan respons filter *moving average*. Jika `N` diperbesar menjadi 20, hasil filter lebih stabil karena menggunakan lebih banyak data, tetapi respons terhadap perubahan suhu menjadi lebih lambat. Sebaliknya, jika `N` diperkecil menjadi 2, filter lebih cepat merespons perubahan suhu, tetapi hasilnya lebih mudah berfluktuasi akibat noise. Oleh karena itu, nilai `N` perlu disesuaikan dengan kebutuhan sistem.
4. Modifikasi program agar ESP32 juga menghitung simpangan baku dari data pada buffer, dan berikan penjelasan di setiap baris kode yang ditambahkan dalam bentuk README.md!

```cpp
#include <Arduino.h>
#include <math.h>

const int N = 5;
float buffer[N];
int indeks = 0;
int jumlah = 0;

float suhuMin = 1000.0;
float suhuMax = -1000.0;

// Fungsi untuk menghasilkan suhu dummy
float bacaSuhuMock() {
  static unsigned long jumlahBaca = 0;
  jumlahBaca++;

  float suhuDasar = 28.0 + 2.0 * sin(jumlahBaca * 0.08);
  float noise = random(-5, 6) * 0.1;
  float suhu = suhuDasar + noise;

  // Simulasi lonjakan suhu setiap 25 pembacaan
  if (jumlahBaca % 25 == 0) {
    suhu += 8.0;
  }

  return suhu;
}

// Menghitung moving average dari buffer
float hitungMovingAverage(float nilaiBaru) {
  buffer[indeks] = nilaiBaru;
  indeks = (indeks + 1) % N;

  if (jumlah < N) {
    jumlah++;
  }

  float total = 0.0;
  for (int i = 0; i < jumlah; i++) {
    total += buffer[i];
  }

  return total / jumlah;
}

// Menghitung simpangan baku nilai di dalam buffer
float hitungSimpanganBaku() {
  if (jumlah == 0) {
    return 0.0;
  }

  float total = 0.0;
  for (int i = 0; i < jumlah; i++) {
    total += buffer[i];
  }

  float mean = total / jumlah;
  float jumlahKuadratSelisih = 0.0;

  for (int i = 0; i < jumlah; i++) {
    float selisih = buffer[i] - mean;
    jumlahKuadratSelisih += selisih * selisih;
  }

  // Simpangan baku populasi
  float varians = jumlahKuadratSelisih / jumlah;
  return sqrt(varians);
}

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(A0));

  Serial.println(
    "--- Percobaan 5A: Moving Average dan Simpangan Baku ---"
  );
}

void loop() {
  float suhu = bacaSuhuMock();
  float suhuFilter = hitungMovingAverage(suhu);
  float stdDev = hitungSimpanganBaku();

  if (suhu < suhuMin) {
    suhuMin = suhu;
  }

  if (suhu > suhuMax) {
    suhuMax = suhu;
  }

  Serial.print("Mentah: ");
  Serial.print(suhu, 2);

  Serial.print(" | Moving Average: ");
  Serial.print(suhuFilter, 2);

  Serial.print(" | Simpangan Baku: ");
  Serial.print(stdDev, 3);

  Serial.print(" | Min: ");
  Serial.print(suhuMin, 2);

  Serial.print(" | Max: ");
  Serial.println(suhuMax, 2);

  delay(2000);
}
```

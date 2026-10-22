## Detail Percobaan
Percobaan 5B membahas pengolahan data suhu pada sisi komputer menggunakan Python. Program menerima data suhu yang dipublikasikan ESP8266 melalui broker MQTT, menyimpan waktu penerimaan dan nilai suhu ke file CSV, menghitung statistik, mendeteksi anomali menggunakan metode *z-score*, serta menampilkan grafik suhu. Sensor yang digunakan adalah DHT11. Program mengumpulkan 30 sampel sebelum menyelesaikan proses akuisisi dan analisis.

## Penjelasan Code
Program mengimpor library `json`, `time`, `paho.mqtt.client`, `pandas`, dan `matplotlib.pyplot`. Variabel `BROKER`, `PORT`, dan `TOPIC` menentukan alamat broker MQTT, port komunikasi, serta topik data yang diterima. Nilai `TOPIC` harus disamakan dengan `topicData` pada program ESP8266, sedangkan `JUMLAH\_SAMPEL = 30` menentukan banyak data yang dikumpulkan. Daftar `data` menampung waktu penerimaan dan nilai suhu. Fungsi `on\_connect()` berlangganan ke topik setelah koneksi berhasil. Fungsi `on\_message()` memproses pesan, mengubah payload JSON menjadi objek Python, mengambil nilai `suhu`, dan mengabaikan pesan yang tidak valid. Data valid ditambahkan ke daftar bersama waktu penerimaannya. Setelah 30 sampel terkumpul, program memutus koneksi MQTT. Data kemudian diubah menjadi DataFrame menggunakan pandas dan disimpan ke `data\_suhu.csv`. Program menghitung rata-rata dan simpangan baku, menentukan nilai *z score*, menandai data dengan nilai absolut *z-score* lebih dari 2 sebagai anomali, serta menampilkan ringkasan statistik. Terakhir, matplotlib membuat grafik suhu, memberi penanda pada data anomali, menampilkan garis rata-rata, dan menyimpan grafik sebagai `grafik\_suhu.png`.

## Penjelasan Setiap Fungsi
- `on\_connect(client, userdata, flags, reason\_code, properties)`\ 
Dipanggil ketika program terhubung ke broker MQTT. Fungsi ini menampilkan kode koneksi dan menjalankan `client.subscribe(TOPIC)`agar program menerima pesan dari topik yang ditentukan.

- `on\_message(client, userdata, msg)`\
Dipanggil ketika pesan MQTT diterima. Fungsi ini mendekode payload menjadi teks, mengubahnya dari JSON menjadi objek Python, lalu mengambil nilai `suhu`. Jika format pesan tidak valid atau kunci `suhu` tidak tersedia, program menampilkan pesan kesalahan dan menghentikan pemrosesan pesan tersebut. Data valid disimpan bersama waktu penerimaannya. Ketika jumlah data mencapai `JUMLAH\_SAMPEL`, fungsi memutus koneksi MQTT.

- `client.connect(BROKER, PORT)`\
Memulai koneksi ke broker MQTT menggunakan alamat dan port yang ditentukan.

- `client.loop\_forever()`\
Menjalankan proses komunikasi MQTT secara terus-menerus agar program dapat menerima dan menangani pesan yang masuk.

- `pd.DataFrame(data)`\
Mengubah daftar data yang dikumpulkan menjadi DataFrame agar mudah diolah dan disimpan dalam bentuk tabel.

- `df.to\_csv("data\_suhu.csv", index=False)`\
Menyimpan data waktu dan suhu ke file CSV tanpa menambahkan kolom indeks DataFrame.

- `plt.plot()`\
Membuat grafik garis yang menunjukkan perubahan suhu berdasarkan urutan data.

- `plt.scatter()`\
Menandai titik data yang terdeteksi sebagai anomali pada grafik.

- `plt.axhline()`\
Menambahkan garis horizontal sebagai penanda nilai rata-rata suhu.

- `plt.savefig()` dan `plt.show()`\
`plt.savefig()` menyimpan grafik ke file `grafik\_suhu.png`, sedangkan `plt.show()` menampilkan grafik pada layar.

## Penjelasan Percabangan atau Conditional
Program menggunakan blok `try-except` di dalam `on\_message()` untuk menangani pesan yang tidak dapat diproses. Jika payload tidak dapat diubah menjadi JSON, kunci `suhu` tidak tersedia, atau nilainya tidak dapat dikonversi menjadi angka, program menampilkan pesan bahwa data tidak valid dan menjalankan `return`. Kondisi `if len(data) >= JUMLAH\_SAMPEL` memeriksa apakah jumlah data sudah mencapai target 30 sampel. Pada tahap analisis, kondisi `if std == 0` mencegah pembagian dengan nol saat simpangan baku bernilai nol. Jika simpangan baku tidak nol, program menghitung *z-score* dengan membagi selisih setiap suhu terhadap rata-rata dengan simpangan baku. Kondisi `df\["zscore"].abs() > 2` menandai data sebagai anomali apabila nilai absolut *z-score* lebih besar dari 2.

## Library atau Dependencies
Program menggunakan library dan perangkat lunak berikut:
1. **`json`**\
Library bawaan Python yang digunakan untuk mengubah payload JSON dari MQTT menjadi objek Python.
2. **`time`**\
Library bawaan Python yang digunakan untuk mencatat waktu penerimaan data dengan `time.strftime()`.
3. **`paho-mqtt`**\
Digunakan untuk menghubungkan program Python ke broker MQTT, berlangganan ke topik data, dan menerima pesan yang dipublikasikan ESP8266.
4. **`pandas`**\
Digunakan untuk menyimpan data dalam DataFrame, menulis data ke file CSV, serta menghitung rata-rata, simpangan baku, nilai minimum, dan maksimum.
5. **`matplotlib`**\
Digunakan untuk membuat, menampilkan, dan menyimpan grafik suhu serta penanda data anomali.
6. **Python 3**\
Diperlukan untuk menjalankan program analisis pada komputer.

Library eksternal dapat dipasang melalui terminal dengan perintah:
```cpp
pip install paho-mqtt pandas matplotlib
```

Program juga memerlukan ESP8266 dengan sensor DHT11 yang memublikasikan data suhu ke broker MQTT. Nilai `TOPIC` pada program Python harus sama dengan topik publikasi yang digunakan ESP8266.

## Jawaban Pertanyaan Percobaan 5B
1. Jelaskan fungsi dari blok `try-except` pada fungsi `on_message()` dan apa yang terjadi apabila blok tersebut dihilangkan!
- Blok `try-except` pada fungsi `on_message()` berfungsi menangani kesalahan saat program membaca payload JSON dan mengubah nilai suhu menjadi angka. Jika data tidak valid atau kunci "suhu" tidak tersedia, program menampilkan pesan kesalahan dan mengabaikan data tersebut. Tanpa blok ini, exception yang tidak tertangani dapat menghentikan program saat menerima pesan bermasalah.
2. Jelaskan arti nilai *z-score* dan mengapa batas `|z| > 2` digunakan sebagai penentu anomali!
- *Z-score* menunjukkan jarak suatu data dari rata-rata dalam satuan simpangan baku. Nilai positif berarti di atas rata-rata, sedangkan nilai negatif berarti di bawah rata-rata. Batas `|z| > 2)` digunakan untuk menandai data yang menyimpang lebih dari dua simpangan baku. Contohnya, suhu 35,22 °C memiliki *z-score* sekitar 3,66 sehingga terdeteksi sebagai anomali. Namun, batas ini hanya aturan praktis dan tidak selalu menunjukkan kesalahan pengukuran.
3. Apa kelemahan metode *z-score* apabila data memiliki tren naik atau turun yang tajam?
- Metode *z-score* kurang efektif pada data dengan tren naik atau turun tajam karena menggunakan rata-rata dan simpangan baku dari seluruh data tanpa mempertimbangkan urutan waktu. Akibatnya, perubahan normal dapat dianggap anomali, sedangkan lonjakan ekstrem dapat membuat anomali lain sulit terdeteksi. Salah satu alternatifnya adalah menggunakan *moving average* sebelum menghitung *z-score*, meskipun metode ini juga dapat mengurangi atau menggeser pengaruh lonjakan suhu.
4. Modifikasi program agar menggunakan metode *moving average* (jendela 5 data) pada data hasil CSV sebelum dihitung *z-score*-nya, kemudian bandingkan jumlah anomali yang terdeteksi, dan berikan penjelasan di setiap baris kode yang ditambahkan dalam bentuk README.md!

```cpp
import json
import time
import math

import paho.mqtt.client as mqtt
import pandas as pd
import matplotlib.pyplot as plt

BROKER = "broker.hivemq.com"
PORT = 1883
TOPIC = "unsoed/tk245004/kelompokdupan/data"
JUMLAH_SAMPEL = 30
WINDOW = 5

data = []


def on_connect(client, userdata, flags, reason_code, properties):
    print("Terhubung ke broker, kode:", reason_code)

    if reason_code == 0:
        client.subscribe(TOPIC)
        print("Berlangganan topik:", TOPIC)


def on_message(client, userdata, msg):
    try:
        payload = json.loads(msg.payload.decode("utf-8"))
        suhu = float(payload["suhu"])

        if not math.isfinite(suhu):
            raise ValueError("Nilai suhu bukan angka yang valid")

    except (json.JSONDecodeError, ValueError, KeyError, TypeError):
        print("Data tidak valid, diabaikan")
        return

    data.append({
        "waktu": time.strftime("%Y-%m-%d %H:%M:%S"),
        "suhu": suhu
    })

    print(
        f"[{len(data)}/{JUMLAH_SAMPEL}] "
        f"Suhu diterima = {suhu:.2f} °C"
    )

    if len(data) >= JUMLAH_SAMPEL:
        client.disconnect()


# Tahap 1: Mengumpulkan data suhu melalui MQTT
client = mqtt.Client(
    mqtt.CallbackAPIVersion.VERSION2
)
client.on_connect = on_connect
client.on_message = on_message

print(f"Mulai mengumpulkan {JUMLAH_SAMPEL} data dari MQTT...")
client.connect(BROKER, PORT)
client.loop_forever()


# Tahap 2: Menyimpan data mentah ke CSV
df = pd.DataFrame(data)

if df.empty:
    raise SystemExit(
        "Tidak ada data yang diterima. "
        "Periksa koneksi MQTT dan kesesuaian topik."
    )

df.to_csv("data_suhu.csv", index=False)
print("\nData mentah tersimpan di data_suhu.csv")


# Tahap 3A: Deteksi anomali tanpa moving average
mean_tanpa_ma = df["suhu"].mean()
std_tanpa_ma = df["suhu"].std()

if pd.isna(std_tanpa_ma) or std_tanpa_ma == 0:
    df["zscore_tanpa_ma"] = 0.0
else:
    df["zscore_tanpa_ma"] = (
        df["suhu"] - mean_tanpa_ma
    ) / std_tanpa_ma

df["anomali_tanpa_ma"] = (
    df["zscore_tanpa_ma"].abs() > 2
)


# Tahap 3B: Moving average dengan jendela 5 data
df["suhu_ma"] = df["suhu"].rolling(
    window=WINDOW,
    min_periods=WINDOW
).mean()


# Tahap 3C: Deteksi anomali setelah moving average
data_ma_valid = df["suhu_ma"].dropna()

if len(data_ma_valid) < 2:
    mean_dengan_ma = data_ma_valid.mean()
    std_dengan_ma = float("nan")
else:
    mean_dengan_ma = data_ma_valid.mean()
    std_dengan_ma = data_ma_valid.std()

if pd.isna(std_dengan_ma) or std_dengan_ma == 0:
    df["zscore_dengan_ma"] = float("nan")
    df["anomali_dengan_ma"] = False
else:
    df["zscore_dengan_ma"] = (
        df["suhu_ma"] - mean_dengan_ma
    ) / std_dengan_ma

    df["anomali_dengan_ma"] = (
        df["zscore_dengan_ma"].abs() > 2
    ).fillna(False)


# Tahap 4: Menampilkan perbandingan hasil
jumlah_anomali_tanpa_ma = int(
    df["anomali_tanpa_ma"].sum()
)
jumlah_anomali_dengan_ma = int(
    df["anomali_dengan_ma"].sum()
)

print("\n--- HASIL ANALISIS DATA SUHU ---")
print(f"Jumlah sampel              : {len(df)}")
print(f"Rata-rata suhu mentah      : {mean_tanpa_ma:.2f} °C")
print(f"Simpangan baku suhu mentah : {std_tanpa_ma:.2f} °C")
print(f"Jumlah anomali tanpa MA    : {jumlah_anomali_tanpa_ma}")
print(f"Rata-rata suhu MA          : {mean_dengan_ma:.2f} °C")
print(f"Simpangan baku suhu MA     : {std_dengan_ma:.2f} °C")
print(f"Jumlah anomali dengan MA   : {jumlah_anomali_dengan_ma}")


# Tahap 5: Menyimpan hasil analisis
df.to_csv("data_suhu_analisis.csv", index=False)
print("\nHasil analisis tersimpan di data_suhu_analisis.csv")


# Tahap 6: Membuat grafik perbandingan
plt.figure(figsize=(12, 5))

plt.plot(
    df.index,
    df["suhu"],
    label="Suhu Mentah",
    color="lightgray",
    linestyle="--",
    marker="."
)

plt.plot(
    df.index,
    df["suhu_ma"],
    label="Moving Average (5 data)",
    color="blue",
    linewidth=2
)

anom_tanpa = df[df["anomali_tanpa_ma"]]
plt.scatter(
    anom_tanpa.index,
    anom_tanpa["suhu"],
    color="red",
    s=80,
    label="Anomali tanpa MA",
    zorder=4
)

anom_dengan = df[df["anomali_dengan_ma"]]
if not anom_dengan.empty:
    plt.scatter(
        anom_dengan.index,
        anom_dengan["suhu_ma"],
        color="purple",
        s=100,
        marker="x",
        label="Anomali dengan MA",
        zorder=5
    )

if not pd.isna(mean_dengan_ma):
    plt.axhline(
        mean_dengan_ma,
        color="gray",
        linestyle=":",
        label="Rata-rata MA"
    )

plt.xlabel("Urutan Sampel Data")
plt.ylabel("Suhu (°C)")
plt.title("Perbandingan Deteksi Anomali Sebelum dan Sesudah MA")
plt.legend()
plt.tight_layout()
plt.savefig("grafik_suhu.png")
print("Grafik tersimpan sebagai grafik_suhu.png")
plt.show()
```

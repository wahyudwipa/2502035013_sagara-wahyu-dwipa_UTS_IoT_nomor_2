#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Wire.h>
#include <BH1750.h>

// Definisi pin
const int DHT_PIN = 4; // Sensor DHT11
const int LED_PIN = 2; // LED
const int LIGHT_SENSOR_ADDRESS = 0x23; // Alamat I2C sensor cahaya

// Definisi tipe sensor
const int DHT_TYPE = DHT11; // Sensor DHT11
const int LIGHT_SENSOR_TYPE = BH1750::ONE_TIME_HIGH_RES_MODE; // Resolusi 1 lx

// Objek sensor
DHT dht(DHT_PIN, DHT_TYPE); // Sensor DHT11
BH1750 lightMeter; // Alamat I2C 0x23

void setup() {
  Serial.begin(115200); // Inisialisasi komunikasi serial
  Wire.begin(21, 22); // SDA, SCL
  dht.begin(); // Inisialisasi sensor suhu/kelembapan
  lightMeter.begin(); // Inisialisasi sensor cahaya
 
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  static unsigned long lastTempTime = 0; //variabel static untuk pembacaan suhu setiap 7 detik
  static unsigned long lastHumidityTime = 0; //variabel static untuk pembacaan kelembapan setiap 4 detik
  static unsigned long lastLightTime = 0; //variabel static untuk pembacaan cahaya setiap 2 detik

  // Baca suhu setiap 0 detik
  if (millis() - lastTempTime >= 000) {
    float temperature = dht.readTemperature();  //membaca suhu dengan sensor DHT11
    if (!isnan(temperature)) { //jika suhu bukan angka, print suhu
      Serial.print("Suhu: "); //print suhu
      Serial.print(temperature); 
      Serial.println(" C"); 
    } else {
      Serial.println("Gagal membaca suhu!");  //jika suhu bukan angka, print pesan error
    }
    lastTempTime = millis(); //untuk membaca suhu setiap 7 detik
  }

  // Baca kelembapan setiap 1 detik
  if (millis() - lastHumidityTime >= 1000) { //untuk membaca kelembapan setiap 4 detik
    float humidity = dht.readHumidity(); //membaca kelembapan dengan sensor DHT11
    if (!isnan(humidity)) { //jika kelembapan bukan angka, print kelembapan
      Serial.print("Kelembapan: "); //print kelembapan
      Serial.print(humidity);
      Serial.println(" %");
    } else {
      Serial.println("Gagal membaca kelembapan!"); //jika kelembapan bukan angka, print pesan error
    }
    lastHumidityTime = millis();
  }

  // Baca cahaya setiap 3 detik
  if (millis() - lastLightTime >= 3000) {
    uint16_t lux = lightMeter.readLightLevel();  //membaca level cahaya dengan sensor BH1750
    if (!isnan(lux)) { //jika level cahaya bukan angka, print level cahaya
      Serial.print("Cahaya: "); //print level cahaya
      Serial.print(lux);
      Serial.println(" lx");
    } else {
      Serial.println("Gagal membaca cahaya!"); //jika level cahaya bukan angka, print pesan error
    }
    lastLightTime = millis(); //untuk membaca level cahaya setiap 2 detik
  }
}
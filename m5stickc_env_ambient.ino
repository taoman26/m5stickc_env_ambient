#include <M5StickC.h>
#include "DHT12.h"
#include <Wire.h>
#include "Adafruit_Sensor.h"
#include <Adafruit_BMP280.h>
#include "Ambient.h"

DHT12 dht12;
Adafruit_BMP280 bme;

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  6        /* Time ESP32 will go to sleep (in seconds) */

WiFiClient client;
Ambient ambient;

const char* ssid = "your_ssid"; // WiFiのSSID
const char* password = "your_password"; // WiFiのパスフレーズ

unsigned int channelId = CHANNEL_ID; // AmbientのチャネルID
const char* writeKey = "WRITE_KEY"; // Ambientのライトキー

void setup() {
    M5.begin();
    M5.Axp.ScreenBreath(10);    // 画面の輝度を少し下げる
    M5.Lcd.setRotation(3);      // 左を上にする
    M5.Lcd.setTextSize(2);      // 文字サイズを2にする
    M5.Lcd.fillScreen(BLACK);   // 背景を黒にする
    M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK); // 文字色を白色、背景を黒に明示的に設定

    Wire.begin(0,26);               // I2Cを初期化する
    while (!bme.begin(0x76)) {  // BMP280を初期化する
        M5.Lcd.println("BMP280 init fail");
    }

    WiFi.begin(ssid, password);  //  Wi-Fi APに接続 ----A
    while (WiFi.status() != WL_CONNECTED) {  //  Wi-Fi AP接続待ち
        delay(500);
        Serial.print("Now, Connecting...");
    }
    Serial.print("WiFi connected\r\nIP address: ");

    //esp_deep_sleep(TIME_TO_SLEEP * uS_TO_S_FACTOR); //  ----C
}

void loop() {
    float tmp = dht12.readTemperature();
    float hum = dht12.readHumidity();
    float pressure = bme.readPressure();
    double vbat = M5.Axp.GetVbatData() * 1.1 / 1000;  // バッテリー電圧を取得

    M5.Lcd.setCursor(0, 0, 1);
    M5.Lcd.printf("temp: %4.1f'C\r\n", tmp);
    M5.Lcd.printf("humid:%4.1f%%\r\n", hum);
    M5.Lcd.printf("press:%4.0fhPa\r\n", pressure / 100);
    M5.Lcd.printf("vbat: %4.2fV\r\n", vbat);
    M5.Lcd.println(WiFi.localIP()); // IPアドレスを表示

    ambient.begin(channelId, writeKey, &client); // チャネルIDとライトキーを指定してAmbientの初期化

    // 温度、湿度、気圧、バッテリー電圧の値をAmbientに送信する ----B
    ambient.set(1, tmp);
    ambient.set(2, hum);
    ambient.set(3, pressure / 100);
    ambient.set(4, vbat);

    ambient.send();

    // 5分待機
    delay(300000);
}

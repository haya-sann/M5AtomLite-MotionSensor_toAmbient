#include <Arduino.h>
#include <M5Unified.h>
#include <WiFiManager.h> // Include the WiFiManager library
WiFiManager wifiManager;
#include <Adafruit_NeoPixel.h>
#define LED_PIN 27
Adafruit_NeoPixel pixels(1, LED_PIN);

uint8_t red = 0, green = 1, blue = 2, white = 3, count = 0;
uint32_t colors[] = {pixels.Color(125, 0, 0), pixels.Color(0, 125, 0), pixels.Color(0, 0, 125), pixels.Color(125, 125, 125)};
const uint8_t COLORS_LEN = (uint8_t)(sizeof(colors) / sizeof(colors[0]));


void setup() {
  // M5Atomの初期化
  M5.begin();
  // シリアル通信の初期化
  // Serial.begin(115200); //これはM5.begin()の中でやっているので不要
    // LEDを赤色に点灯する
  delay(1000); // 1秒待つ
  pixels.clear();
  pixels.setPixelColor(0, colors[red]);
  pixels.show();
  Serial.println("Hello, world!");
  // M5.dis.clear();  // Clear the LED
  // M5.dis.drawpix(0, 0x00ff00);  // Light the LED with the specified RGB color
  pinMode(32, INPUT);  // Set pin 32 to input mode. 
    // ランダムシードの初期化
  randomSeed(analogRead(0));
    WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP    

    wifiManager.setConfigPortalBlocking(false);
    wifiManager.setConfigPortalTimeout(60); // Set timeout for the configuration portal
    //automatically connect using saved credentials if they exist
    //If connection fails it starts an access point with the specified name

    // wifiManager.resetSettings();

    // Connect to WiFi using WiFiManager
   if(wifiManager.autoConnect("AutoConnectAP")){
        Serial.println("connected...yeey :)");
    }
    else {
        Serial.println("Configportal running");
    }
    // Print the assigned IP address
    Serial.println("Connected to WiFi");
    Serial.print("Server IP Address: ");
    Serial.println(WiFi.localIP());

}

int prevMotionSensor = 0; // 前回のモーションセンサーの状態を保持する変数
void loop() {
      // 20から80までのランダムな値を生成
  int sensorData = random(20, 81); // 上限は排他的なので81を指定すると80までの値が生成される
  int motionSensor = digitalRead(32); // GPIO33はADCピン
  if (motionSensor == 1 && prevMotionSensor == 0) {
      Serial.println("動作指示がありました");
      // sensorDataの値をシリアルモニターに出力
      Serial.println("Sensor Data: " + String(sensorData) );
      for (int i = 0; i < 2; i++) {
        pixels.clear();
        pixels.setPixelColor(0, colors[blue]);
        pixels.show();
        delay(500);
        pixels.clear();
        pixels.setPixelColor(0, colors[white]);
        pixels.show();
        delay(500);
      }
      pixels.clear();
      pixels.show();
    // motionSensorが0から1に変化した場合にLEDを2回点滅させる
      // for (int i = 0; i < 2; i++) {
      //     M5.dis.drawpix(0, 0xff0000);  // RED  红色
      //     // M5.dis.drawpix(0, CRGB::Red); // 内蔵LEDを赤色に設定
      //     delay(500); // 500ミリ秒待つ
      //     M5.dis.clear(); // LEDを消す
      //     delay(500); // 500ミリ秒待つ
      // 状態をシリアルモニターに出力
      }
  prevMotionSensor = motionSensor; // 現在のモーションセンサーの状態をprevMotionSensorに保存する
    // Serial.println("motionSensor:" + String(motionSensor) + " prevMotionSensor:" + String(prevMotionSensor)); 
  // 状態をシリアルモニターに出力
  delay(1000);
}
// #endif
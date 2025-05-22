#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "indicator_model.h"  // Your generated Simulink logic

#define LEFT_LED 21
#define RIGHT_LED 22
#define LEFT_BTN 18
#define RIGHT_BTN 19

// BLE control flags
bool ble_left = false;
bool ble_right = false;
bool ble_hazard = false;

unsigned long lastTick = 0;

// BLE callback class
class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    String value = pCharacteristic->getValue().c_str(); // Use Arduino String

    value.trim(); // Removes \r and \n

    Serial.print("BLE Command: ");
    Serial.println(value);

    if (value == "LEFT") {
      ble_left = true; ble_right = false; ble_hazard = false;
      Serial.println("BLE: LEFT mode");
    } else if (value == "RIGHT") {
      ble_right = true; ble_left = false; ble_hazard = false;
      Serial.println("BLE: RIGHT mode");
    } else if (value == "HAZARD") {
      ble_hazard = true; ble_left = false; ble_right = false;
      Serial.println("BLE: HAZARD mode");
    } else if (value == "OFF") {
      ble_left = ble_right = ble_hazard = false;
      Serial.println("BLE: OFF");
    } else {
      Serial.println("BLE: Unknown command");
    }
  }
};

void setupBLE() {
  BLEDevice::init("ESP32_Indicator");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService("12345678-1234-1234-1234-1234567890ab");

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
    "abcdef01-1234-1234-1234-abcdefabcdef",
    BLECharacteristic::PROPERTY_WRITE
  );

  pCharacteristic->setCallbacks(new MyCallbacks());
  pCharacteristic->setValue("ready");

  pService->start();
  pServer->getAdvertising()->start();

  Serial.println("BLE service started...");
}

void setup() {
  Serial.begin(115200);
  pinMode(LEFT_LED, OUTPUT);
  pinMode(RIGHT_LED, OUTPUT);
  pinMode(LEFT_BTN, INPUT_PULLUP);
  pinMode(RIGHT_BTN, INPUT_PULLUP);
  setupBLE();
  indicator_model_initialize();
}

void loop() {
  unsigned long now = millis();

  if (now - lastTick >= 100) {
    lastTick = now;

    bool leftBtnState = digitalRead(LEFT_BTN) == LOW;
    bool rightBtnState = digitalRead(RIGHT_BTN) == LOW;

    // BLE overrides button input
    if (ble_left) {
      leftBtnState = true; rightBtnState = false;
    } else if (ble_right) {
      leftBtnState = false; rightBtnState = true;
    } else if (ble_hazard) {
      leftBtnState = true; rightBtnState = true;
    }

    bool leftLED = false;
    bool rightLED = false;
    indicator_model_step(leftBtnState, rightBtnState, &leftLED, &rightLED);

    digitalWrite(LEFT_LED, leftLED ? HIGH : LOW);
    digitalWrite(RIGHT_LED, rightLED ? HIGH : LOW);

    Serial.print("LEFT_LED: ");
    Serial.print(leftLED);
    Serial.print(" | RIGHT_LED: ");
    Serial.println(rightLED);
  }
}   
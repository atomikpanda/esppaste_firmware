#include <Arduino.h>
#include <USB.h>
#include <USBHID.h>
#include <USBHIDKeyboard.h>
#include <string>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
USBHIDKeyboard Keyboard;

const int buttonPin = 0;        // input pin for pushbutton
int previousButtonState = HIGH; // for checking the state of a pushButton
bool deviceConnected = false;
std::string bleData = "";

class MyCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic)
  {
    std::string value = pCharacteristic->getValue().c_str();
    if (value.length() > 0)
    {
      bleData = value;
    }
  }

  void onConnect(BLEServer *pServer)
  {
    deviceConnected = true;
  }

  void onDisconnect(BLEServer *pServer)
  {
    deviceConnected = false;
    // start advertising
    pServer->getAdvertising()->start();
  }
};

// setup BLE characteristic to receive data to type out

BLECharacteristic *pCharacteristic;

#define SERVICE_UUID "12345678-1234-1234-1234-123456789012"
#define CHARACTERISTIC_UUID "87654321-4321-4321-4321-210987654321"

void setupBLEDataInput()
{
  BLEDevice::init("ESP32_BLE_Keyboard");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_WRITE);
  pCharacteristic->setCallbacks(new MyCallbacks());
  pCharacteristic->addDescriptor(new BLE2902());
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
}

void setup()
{
  // make the pushButton pin an input:
  pinMode(buttonPin, INPUT_PULLUP);
  // initialize control over the keyboard:

  Keyboard.begin();
  USB.begin();
  setupBLEDataInput();
  delay(2000);
}

void loop()
{

  // read the pushbutton:
  int buttonState = digitalRead(buttonPin);
  // if the button state has changed,
  if ((buttonState != previousButtonState)
      // and it's currently pressed:
      && (buttonState == LOW))
  {
    // type out a message
    Keyboard.print(bleData.c_str());
  }
  // save the current button state for comparison next time:
  previousButtonState = buttonState;
}
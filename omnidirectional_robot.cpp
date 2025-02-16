#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SparkFun_TB6612.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// Motor Driver Configuration
#define AIN1 12
#define AIN2 13
#define PWMA 14
#define BIN1 25
#define BIN2 26
#define PWMB 27
#define STBY 33

// WiFi Credentials
const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";

// Web Server Setup
AsyncWebServer server(80);

// Motor Setup
Motor motor1 = Motor(AIN1, AIN2, PWMA, 1);
Motor motor2 = Motor(BIN1, BIN2, PWMB, 1);

// OLED Display Setup
Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);

void setup() {
    Serial.begin(115200);

    // Initialize Motors
    pinMode(STBY, OUTPUT);
    digitalWrite(STBY, HIGH);

    // Initialize OLED Display
    if (!display.begin(0x3C, true)) {
        Serial.println("SH1107 OLED initialization failed");
    } else {
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(SH110X_WHITE);
        display.setCursor(0, 0);
        display.println("Omnidirectional Robot");
        display.display();
    }

    // Connect to WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi Connected!");

    // Define Web Server Routes
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", "Omnidirectional Robot Controller Active");
    });

    server.on("/forward", HTTP_GET, [](AsyncWebServerRequest *request) {
        moveForward();
        request->send(200, "text/plain", "Moving Forward");
    });

    server.on("/backward", HTTP_GET, [](AsyncWebServerRequest *request) {
        moveBackward();
        request->send(200, "text/plain", "Moving Backward");
    });

    server.on("/left", HTTP_GET, [](AsyncWebServerRequest *request) {
        moveLeft();
        request->send(200, "text/plain", "Turning Left");
    });

    server.on("/right", HTTP_GET, [](AsyncWebServerRequest *request) {
        moveRight();
        request->send(200, "text/plain", "Turning Right");
    });

    server.begin();
}

// Movement Functions
void moveForward() {
    motor1.drive(200);
    motor2.drive(200);
}

void moveBackward() {
    motor1.drive(-200);
    motor2.drive(-200);
}

void moveLeft() {
    motor1.drive(-200);
    motor2.drive(200);
}

void moveRight() {
    motor1.drive(200);
    motor2.drive(-200);
}

void loop() {
    // Standby loop
}

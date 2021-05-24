#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <Blynk.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_PRINT Serial
#define REPORTING_PERIOD_MS     1000

char auth[] = "";
char ssid[] = "";
char pass[] = "";
WidgetLCD lcd(V10);
PulseOximeter covimate;
uint32_t tsLastReport = 0;

void BeatDetected()
{
  Serial.println("Beat!");
  }
void setup()
{
  Serial.begin(115200);
    Blynk.begin(auth, ssid, pass);
      Serial.print("Initializing pulse oximeter..");
  if (!covimate.begin()) {
      Serial.println("FAILED");
          for (;;);
            } else {
                Serial.println("SUCCESS");
                  }

  covimate.setOnBeatDetectedCallback(BeatDetected);
  }
void loop()
{

  covimate.update();
    Blynk.run();
      if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
          Serial.print("Heart rate:");
              Serial.print(covimate.getHeartRate());
                  Serial.print("bpm / SpO2:");
                      Serial.print(covimate.getSpO2());
                          Serial.println("%");
                              Blynk.virtualWrite(V15, covimate.getHeartRate());
                                  Blynk.virtualWrite(V7, covimate.getSpO2());
    tsLastReport = millis();
      }
        covimate.update();
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
      if (covimate.getSpO2() < 94 || 100 < covimate.getHeartRate() || 60 > covimate.getHeartRate())
          { 
                lcd.clear();
                      lcd.print(0,0, "ALERT");
                          }
    tsLastReport = millis();
      }
        covimate.update();
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
      if (covimate.getSpO2() > 94 || 100 > covimate.getHeartRate() || 60 < covimate.getHeartRate())
          { 
                lcd.clear();
                      lcd.print(0,0, "EVERYTHING IS");
                            lcd.print(4,1, "NORMAL");
                                }
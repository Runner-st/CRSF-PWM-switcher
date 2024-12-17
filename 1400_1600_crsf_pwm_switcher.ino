#include <CrsfSerial.h>
#include <HardwareSerial.h>
#include "../generic/common.h"

#define PIN_SERIAL2_TX (8u)
#define PIN_SERIAL2_RX (9u)
#define PWM_PIN 2    // PWM output pin for sending signal

CrsfSerial crsf(Serial2, CRSF_BAUDRATE);
void setup() {
  Serial.begin(115200);
  Serial2.begin(CRSF_BAUDRATE);
  crsf.begin();
  crsf.onPacketChannels = &packetChannels;
  crsf.onLinkDown = &noConnection;
}

void loop() {
  crsf.loop();
}

void packetChannels() {
  int Ch8Value = crsf.getChannel(8);
  // Check if Ch8 value is between 1400 and 1600
  if (Ch8Value >= 1400 && Ch8Value <= 1600) {
      analogWrite(PWM_PIN, 255);
  } else {
      analogWrite(PWM_PIN, 0);
  }
}

void noConnection() {
  analogWrite(PWM_PIN, 0);
}
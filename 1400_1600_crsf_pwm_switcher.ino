#include <CrsfSerial.h>
#include <HardwareSerial.h>
#include "../generic/common.h"
#include "RP2040_PWM.h"

#define PIN_SERIAL2_TX (8u)
#define PIN_SERIAL2_RX (9u)
#define pinToSend 2    // PWM output pin for sending signal

// creates pwm instance
RP2040_PWM* PWM_Instance;

//us span in which the 100% duty cycle signal going to be sent to relay
int spanStart = 1400;
int spanEnd = 1600;

CrsfSerial crsf(Serial2, CRSF_BAUDRATE);

void setup() {
  //assigns pin 2, with frequency of 10 KHz and a duty cycle of 0%
  PWM_Instance = new RP2040_PWM(pinToSend, 10000, 0);

  Serial.begin(115200);
  crsf.begin();
  crsf.onPacketChannels = &packetChannels;
  crsf.onLinkDown = &noConnection;
}

void loop() {
  crsf.loop();
}

void packetChannels() {
  int Ch8Value = crsf.getChannel(8);
  // Check if Ch8 value is within the desired span
  if (Ch8Value >= spanStart && Ch8Value <= spanEnd) {
    PWM_Instance->setPWM(pinToSend, 10000, 100);
  } else {
    PWM_Instance->setPWM(pinToSend, 10000, 0);
  }
}

void noConnection() {
  PWM_Instance->setPWM(pinToSend, 10000, 0);
}
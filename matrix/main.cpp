#include <Arduino.h>

#define IND1_PIN 6
#define IND2_PIN 7
#define IND3_PIN 8

#define SEGE_PIN 2
#define SEGD_PIN 3
#define SEGC_PIN 4
#define SEGG_PIN A3
#define SEGF_PIN A2
#define SEGA_PIN A1
#define SEGB_PIN A0

#define FPS 70
#define NDIGITS 3
#define DELAY_MS (1000 / FPS / NDIGITS)

void setup()
{
  pinMode(IND1_PIN, OUTPUT);
  pinMode(IND2_PIN, OUTPUT);
  pinMode(IND3_PIN, OUTPUT);

  pinMode(SEGA_PIN, OUTPUT);
  pinMode(SEGB_PIN, OUTPUT);
  pinMode(SEGC_PIN, OUTPUT);
  pinMode(SEGD_PIN, OUTPUT);
  pinMode(SEGE_PIN, OUTPUT);
  pinMode(SEGF_PIN, OUTPUT);
  pinMode(SEGG_PIN, OUTPUT);
}

void selectIndicator(int pin)
{
  digitalWrite(IND1_PIN, pin != IND1_PIN);
  digitalWrite(IND2_PIN, pin != IND2_PIN);
  digitalWrite(IND3_PIN, pin != IND3_PIN);
}

void showDigit(int d)
{
  digitalWrite(SEGA_PIN, (d != 1) && (d != 4) );
  digitalWrite(SEGB_PIN, (d != 5) && (d != 6) );
  digitalWrite(SEGC_PIN, (d != 2) );
  digitalWrite(SEGD_PIN, (d != 1) && (d != 4) && (d != 7) );
  digitalWrite(SEGE_PIN, (!(d & 1)) && (d != 4) );
  digitalWrite(SEGF_PIN, (d == 0) || ((d >= 4) && (d != 7)) );
  digitalWrite(SEGG_PIN, (d >= 2) && (d != 7) );
}

void loop()
{
  unsigned long tstamp = millis();

  selectIndicator(-1);
  showDigit((tstamp / 10000) % 10);
  selectIndicator(IND1_PIN);
  delay(DELAY_MS);

  selectIndicator(-1);
  showDigit((tstamp / 1000) % 10);
  selectIndicator(IND2_PIN);
  delay(DELAY_MS);

  selectIndicator(-1);
  showDigit((tstamp / 100) % 10);
  selectIndicator(IND3_PIN);
  delay(DELAY_MS);
}

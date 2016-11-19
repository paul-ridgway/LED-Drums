#include <Adafruit_NeoPixel.h>

#define PIN 4
#define LED_COUNT 149

Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);

int offset = 0;
int red = 0;
int green = 0;
int blue = 0;

void setup()
{
  // initialize the digital pin as an output.
  // pinMode(7, OUTPUT);
  pinMode(13, OUTPUT);

  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  digitalWrite(13, LOW);
  delay(250);
  digitalWrite(13, HIGH);

  leds.begin();               // initialize strip
  delay(250);
  digitalWrite(13, LOW);

  introSet();
  delay(100);
  reset();
}

void loop()
{
  digitalWrite(13, ((millis() / 100) % 2) ? HIGH : LOW);

  // if we get a valid byte, read analog ins:
  if (Serial.available() > 0) {
    int start = Serial.read();
    if (start == 255) {
      waitForBuffer(1);
      int cmd = Serial.read();
      if (cmd == 253) {
        reset();
        Serial.write(253);
      } else if (cmd == 254) {
        waitForBuffer(1);
        int count = Serial.read();
        for (int i = 0; i < count; ++i) {
          waitForBuffer(3);
          byte r = Serial.read();
          byte g = Serial.read();
          byte b = Serial.read();
          leds.setPixelColor(i, r, g, b);
        }
        leds.show();
        Serial.write(254);
      }
    }
    Serial.flush();
  }

}


void waitForBuffer(int bytes, const unsigned long timeout) {
  const unsigned long start = millis();
  while (Serial.available() < bytes && (millis() - start) < timeout) {
    ;
  }
}

void waitForBuffer(int bytes) {
  waitForBuffer(bytes, 1000);
}

void introSet() {
  for (int i = -6; i < LED_COUNT; i += 3) {
    //leds.setPixelColor(i-1, 0, 0, 0);
    leds.setPixelColor(i + 0, 255, 0, 0);
    leds.setPixelColor(i + 1, 0, 255, 0);
    leds.setPixelColor(i + 2, 0, 0, 255);
    leds.setPixelColor(i + 3, 255, 225, 0);
    leds.setPixelColor(i + 4, 255, 0, 255);
    leds.setPixelColor(i + 5, 0, 255, 255);
    leds.setPixelColor(i + 6, 255, 255, 255);
    leds.show();
    delay(15);
  }
  leds.show();
}

void reset() {
  for (int i = 0; i < LED_COUNT; ++i) {
    leds.setPixelColor(i, 0, 0, 0);
  }
  leds.show();
}

#include <FastLED.h>

#define NUM_LEDS 78
#define BTN 1
#define DATA_PIN 3

uint8_t i, j, k;
uint8_t count;
uint32_t timer1 = 0;

bool loopOn;
CRGB leds[NUM_LEDS];

void setup() {
  loopOn = true;
  Serial.begin(9600);

  pinMode(BTN, INPUT);

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(10); // SET BRIGHTNESS
  FastLED.show();

}


void loop() {
  if (millis() - timer1 > 200) {

    // Recognize BUTTON PRESS
    if (digitalRead(BTN)) {
      count++;

      if (count > 7) {
        count = 0;
      }
      delay(10);
    }
    timer1 = millis();
  }

  Serial.println(count);

  switch(count) {

    case 0:  // Set NOGGLES pattern in RED and WHITE (eyes)
      loopOn = false;
      if (!loopOn) {
        loopOn = true;
        FastLED.clearData();
        for (i = 0; i < 46; i++)  // Set NOGGLES pattern - RED
        {
          leds[i] = CRGB::Red;
        }
        for (i = 46; i < 54; i++) {
          leds[i] = CRGB::White;  // Set RIGHT-EYE Pattern
        }
        for (i = 62; i < 70; i++) {
          leds[i] = CRGB::White;  // Set LEFT-EYE Pattern
        }
        FastLED.show();
        delay(80);
      }
      break;

    case 1:  // ORANGE NOGGLES
      loopOn = false;
      if (!loopOn) {
        loopOn = true;
        for (i = 0; i < 46; i++) {
          leds[i] = CRGB(255, 103, 0);
          setPixel(i, 255, 103, 0);
          FastLED.show();
        }
        delay(50);
      }
      break;

    case 2:  // YELLOW NOGGLES
      loopOn = false;
      if (!loopOn) {
        loopOn = true;
        for (i = 0; i < 46; i++) {
          leds[i] = CRGB(255, 255, 0);
          FastLED.show();
        }
        delay(50);
      }
      break;

    case 3:  // GREEN NOGGLES
      loopOn = true;
      if (loopOn) {
        loopOn = false;
        for (i = 0; i < 46; i++) {
          leds[i] = CRGB(0, 255, 0);
          FastLED.show();
        }
        delay(50);
      }
      break;

    case 4:  // BLUE NOGGLES
      loopOn = true;
      if (loopOn) {
        loopOn = false;
        for (i = 0; i < 46; i++) {
          leds[i] = CRGB(0, 0, 255);
          FastLED.show();
        }
        delay(50);
      }
      break;

    case 5:  // PINK NOGGLES
      loopOn = true;
      if (loopOn) {
        loopOn = false;
        for (i = 0; i < 46; i++) {
          leds[i] = CRGB(255, 0, 195);
          FastLED.show();
        }
        delay(50);
      }
      break;

    case 6:  // LIGHT CHASER
      loopOn = true;
      lightChaser(0xff, 0x00, 0x00, 10, 64, true, 15);
      break;

    case 7:  // DISCO LIGHTS
      loopOn = true;
      discoLights(5);
      break;
  }
}


void setAll(byte red, byte green, byte blue) {
  for (int i = 0; i < 23; i++) {
    setPixel(i, red, green, blue);
  }
  FastLED.show();
}


void setPixel(int Pixel, byte red, byte green, byte blue) {
  leds[Pixel].r = red;
  leds[Pixel].g = green;
  leds[Pixel].b = blue;
}

void discoLights(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  // Cyle through ALL COLOURS on the wheel
  for (j = 0; j < 256; j++) {
    for (i = 0; i < 46; i++) {
      c = Wheel(((i * 256 / 46) + j) & 255);
      setPixel(i, *c, *(c + 1), *(c + 2));
    }
    FastLED.show();
    delay(SpeedDelay);
  }
}

byte *Wheel(byte WheelPos) {
  static byte c[3];

  if (WheelPos < 85) {
    c[0] = WheelPos * 3;
    c[1] = 255 - WheelPos * 3;
    c[2] = 0;
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    c[0] = 255 - WheelPos * 3;
    c[1] = 0;
    c[2] = WheelPos * 3;
  } else {
    WheelPos -= 170;
    c[0] = 0;
    c[1] = WheelPos * 3;
    c[2] = 255 - WheelPos * 3;
  }

  return c;
}

void lightChaser(byte red, byte green, byte blue, byte chaserSize, byte chaserTrailDecay, boolean chaserRandomDecay, int SpeedDelay) {
  setAll(0, 0, 0);

  for (int i = 0; i < 46 + 46; i++) {

    // FADE LED BRIGHTNESS one step at a time
    for (int j = 0; j < 46; j++) {
      if ((!chaserRandomDecay) || (random(9) > 5)) {
        fadeToBlack(j, chaserTrailDecay);
      }
    }

    // DRAW CHASER LIGHTS
    for (int j = 0; j < chaserSize; j++) {
      if ((i - j < 46) && (i - j >= 0)) {
        setPixel(i - j, red, green, blue);
      }
    }

    FastLED.show();
    delay(SpeedDelay);
  }
}

void fadeToBlack(int ledNo, byte fadeValue) {
  leds[ledNo].fadeToBlackBy(fadeValue);
}

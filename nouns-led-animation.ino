#include <FastLED.h>

#define NUM_LEDS 78 // 78 LEDs in NOGGLES LED DESIGN
#define btn 4       
#define DATA_PIN 0

uint8_t i , j , k ;
uint8_t count ;
uint32_t timer1 = 0 ;

bool loopOn ;

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup()
{
  //Serial.begin(9600);

  pinMode(btn , INPUT);

  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(30);

  // Turn Off all leds in beginning

  for (i = 0 ; i > 78 ; i++ )
  {
    leds[i] = CRGB(0, 0, 0);
    FastLED.show();
  }
}

void loop()
{
  if (millis() - timer1 > 300)    // Recognise button Press and Increment counter
  {
    if (digitalRead(btn))
    {
      count++;

      if (count > 9)
      {
        for (i = 0 ; i < NUM_LEDS ; i++ )
        {
          leds[i] = CRGB(0, 0, 0);
          FastLED.show();
        }
        delay(1500);
        count = 0;
      }
      delay(100);
    }
    timer1 = millis();
  }

  switch (count)
  {
    case 0:                          // Turn Off All the Leds
      loopOn = true ;
      
      if (loopOn)
      {
        loopOn = false ;
        for (i = 0 ; i < NUM_LEDS ; i++ )
        {
          leds[i] = CRGB(0, 0, 0);
          FastLED.show();
        }
      }

      break ;

    case 1:                          // Turn On All the Leds RED and WHITE pattern
      loopOn = true ;
      
      if (loopOn)
      {
        loopOn = false ;

        for (i = 0 ; i < 46 ; i++ )       // Set Clr RED
        {
          leds[i] = CRGB(255, 0, 0);
          FastLED.show();
        }
        for (i = 46 ; i < 54 ; i++ )
        {
          leds[i] = CRGB(255, 255, 255);  // Set White
          FastLED.show();
        }
        for (i = 62 ; i < 70 ; i++ )
        {
          leds[i] = CRGB(255, 255, 255); // Set White
          FastLED.show();
        }

      }
      break ;

    case 2:                         // Turn On All the Leds Orange
      loopOn = true ;
      
      if (loopOn)
      {
        loopOn = false ;
        for (i = 0 ; i < 46 ; i++ )
        {
          leds[i] = CRGB(204, 102, 0);
          FastLED.show();
        }
      }
      break ;

    case 3:           // Turn On All the Leds Yellow
      loopOn = true ;
      
      if (loopOn)
      {
        loopOn = false ;
        for (i = 0 ; i < 46 ; i++ )
        {
          leds[i] = CRGB(255, 255, 0);
          FastLED.show();
        }
      }

      break ;

    case 4:           // Turn On All the Leds Green
      loopOn = true ;
      
      if (loopOn)
      {
        loopOn = false ;
        for (i = 0 ; i < 46 ; i++ )
        {
          leds[i] = CRGB(0, 255, 0);
          FastLED.show();
        }
      }

      break ;

    case 5:           // Turn On All the Leds Blue
      loopOn = true ;
      
      if (loopOn)
      {
        loopOn = false ;
        for (i = 0 ; i < 46 ; i++ )
        {
          leds[i] = CRGB(0, 0, 255);
          FastLED.show();
        }
      }

      break ;

    case 6:           // Turn On All the Leds Purple
      loopOn = true ;
      
      if (loopOn)
      {
        loopOn = false ;
        for (i = 0 ; i < 46 ; i++ )
        {
          leds[i] = CRGB(102, 0, 204);
          FastLED.show();
        }
      }

      break ;

    case 7:           // Turn On All the Leds Pink
      loopOn = true ;
      
      if (loopOn)
      {
        loopOn = false ;
        for (i = 0 ; i < 46 ; i++ )
        {
          leds[i] = CRGB(255, 102, 255);
          FastLED.show();
        }
      }

      break ;

    case 8:           // Turn On All the Leds Chase clr
      loopOn = true ;
      
      meteorRain(0xff, 0x00, 0x00, 10, 64, true, 15);
      


      break ;

    case 9:           // Turn On All the Leds Chase clr
      loopOn = true ;
      //leds[i] = CRGB(0, 0, 255);
      rainbowCycle(5);

      break ;


  }
}

void TwinkleRandom(int Count, int SpeedDelay, boolean OnlyOne) {
  setAll(0, 0, 0);

  for (int i = 0; i < Count; i++) {
    setPixel(random(NUM_LEDS), random(0, 255), random(0, 255), random(0, 255));
    FastLED.show();
    delay(SpeedDelay);
    if (OnlyOne) {
      setAll(0, 0, 0);
    }
  }

  delay(SpeedDelay);
}

void setAll(byte red, byte green, byte blue) {
  for (int i = 0; i < 23; i++ ) {
    setPixel(i, red, green, blue);
  }
  FastLED.show();
}


void setPixel(int Pixel, byte red, byte green, byte blue) {
  // FastLED
  leds[Pixel].r = red;
  leds[Pixel].g = green;
  leds[Pixel].b = blue;
}

void rainbowCycle(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for (j = 0; j < 256; j++) { //cycle of all colors on wheel
    for (i = 0; i < 46; i++)
    {
      c = Wheel(((i * 256 / 46) + j) & 255);
      setPixel(i, *c, *(c + 1), *(c + 2));
    }
    FastLED.show();
    delay(SpeedDelay);
  }
}

byte * Wheel(byte WheelPos) {
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

void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {
  setAll(0, 0, 0);

  for (int i = 0; i < 46 + 46 ; i++) {


    // fade brightness all LEDs one step
    for (int j = 0; j < 46; j++) {
      if ( (!meteorRandomDecay) || (random(10) > 5) ) {
        fadeToBlack(j, meteorTrailDecay );
      }
    }

    // draw meteor
    for (int j = 0; j < meteorSize; j++) {
      if ( ( i - j < 46) && (i - j >= 0) ) {
        setPixel(i - j, red, green, blue);
      }
    }

    FastLED.show();
    delay(SpeedDelay);
  }
}

void fadeToBlack(int ledNo, byte fadeValue) {

  // FastLED
  leds[ledNo].fadeToBlackBy( fadeValue );
}

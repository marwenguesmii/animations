#include "FastLED.h"
#define LED_TYPE WS2812
#define DATA_PIN 5
#define CLOCK_PIN 13
#define NUM_LEDS 60
#define COLOR_ORDER GRB
#define BRIGHTNESS 50
CRGB leds[NUM_LEDS];

uint8_t gHue = 0;  // Used to cycle through rainbow.
uint8_t moveSpeed = 8;  // Higher value moves pixel faster.
uint8_t fadeRate = 200;  // Use lower value to give a fading tail.


//---------------------------------------------------------------
void setup() 
{
  Serial.begin(115200);  // Allows serial monitor output (check baud rate)
  delay(3000);  // 3 second delay
  
  LEDS.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}


//---------------------------------------------------------------
void loop() 
{
  EVERY_N_MILLISECONDS( 50 ) { gHue++; }  // Slowly cycle through the rainbow

  beat8_tail();  // Subroutine to move the pixel!
  
  FastLED.show();  // Display the pixels.

}//end main loop



//===============================================================
void beat8_tail()
{
  EVERY_N_MILLISECONDS( 5 ) {
    fadeToBlackBy( leds, NUM_LEDS, fadeRate);  // Fade out pixels.
  }
  uint16_t pos = beat8(moveSpeed) % NUM_LEDS;  // modulo the position to be within NUM_LEDS
  leds[pos] = CHSV( gHue, 200, 255);
  //Serial.print("pos: "); Serial.println(pos);
}

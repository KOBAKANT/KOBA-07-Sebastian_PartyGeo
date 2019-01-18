#include <FastLED.h>

#define LED_PIN     6
#define COLOR_ORDER GRB
#define CHIPSET     WS2812
#define NUM_LEDS    40

#define BRIGHTNESS  128
#define FRAMES_PER_SECOND 60
CRGB leds[NUM_LEDS];

int hue = 255;
int saturation = 0;




// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  FastLED.show();
  delay(200);

  randomSeed(analogRead(A0));

  for (int i = 0; i < NUM_LEDS; i++) {
    lightOn(i, 255);
  }
  delay(1000);
}

// the loop routine runs over and over again forever:
void loop() {


// turns on multiple fibres, it turns on 3 different postion, with max 6 at the same time.
// argument is indicating max brightness
multipleLightOn2(3, 255);
 

  delay (50);
}

void lightOn(int fibreNum, int maxBrightness) {

  Serial.println(fibreNum);

  for (int brightness = 0; brightness < maxBrightness; brightness = brightness + 5) {
    leds[fibreNum] = CHSV( hue, saturation, brightness);
    FastLED.show();
    delay(5);
  }

  delay (100);

  for (int brightness = maxBrightness; brightness > 0; brightness = brightness - 5) {
    leds[fibreNum] = CHSV( hue, saturation, brightness);
    FastLED.show();
    delay(5);
  }
  leds[fibreNum] = CRGB::Black;
FastLED.show();
}

void multipleLightOn2(int maxPalarell, int maxBrightness) {

    int multiNum[maxPalarell];
    int fibreNum[maxPalarell];
    fibreNum[0] = random(NUM_LEDS);
    multiNum[0] = random(1,6);

    for (int i=1; i<maxPalarell; i++){
      multiNum[i] = random(1,6);
      fibreNum[i] = (fibreNum[i-1] + multiNum[i-1] + random(4))% NUM_LEDS;
    }
    

  for (int brightness = 0; brightness < maxBrightness; brightness = brightness + 5) {
    for (int i=0; i<maxPalarell; i++){
    for (int n = 0; n < multiNum[i]; n++) {
      int f = fibreNum[i] + n;
      f = constrain(f, 0, NUM_LEDS-1);
      leds[f] = CHSV( hue, saturation, brightness);  
    }
    }
    FastLED.show();
    delay(10);
  }

  delay (100);

  for (int brightness = maxBrightness; brightness > 0; brightness = brightness - 5) {
   for (int i=0; i<maxPalarell; i++){
    for (int n = 0; n < multiNum[i]; n++) {
      int f = fibreNum[i] + n;
      f = constrain(f, 0, NUM_LEDS-1);
      leds[f] = CHSV( hue, saturation, brightness);  
    }
    }
    FastLED.show();
    delay(10);
  }

  
  for (int i=0; i<maxPalarell; i++){
    for (int n = 0; n < multiNum[i]; n++) {
      int f = fibreNum[i] + n;
      f = constrain(f, 0, NUM_LEDS-1);
      leds[f] = CRGB::Black; 
    }   
  }
}


void multipleLightOn(int fibreNum, int maxBrightness, int multiNum) {

Serial.print(multiNum);
Serial.print(" : ");
  Serial.println(fibreNum);

  for (int brightness = 0; brightness < maxBrightness; brightness = brightness + 5) {
    for (int n = 0; n < multiNum; n++) {
      int f = fibreNum + n;
      f = constrain(f, 0, NUM_LEDS-1);
      leds[f] = CHSV( hue, saturation, brightness);  
    }
    FastLED.show();
    delay(10);
  }

  delay (100);

  for (int brightness = maxBrightness; brightness > 0; brightness = brightness - 5) {
    for (int n = 0; n < multiNum; n++) {
      int f = fibreNum + n;
      f = constrain(f, 0, NUM_LEDS-1);
      leds[f] = CHSV( hue, saturation, brightness);      
    }
    FastLED.show();
    delay(10);
  }
  for (int n = 0; n < multiNum; n++) {
    int f = fibreNum + n;
      f = constrain(f, 0, NUM_LEDS-1);
      leds[f] = CRGB::Black; 
    
  }
}


void allOff() {
  for (int t = 0; t < NUM_LEDS; t++) {
    leds[t] = CRGB::Black;
    FastLED.show();
  }
}


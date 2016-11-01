#include <Adafruit_NeoPixel.h>
 
#define Count 150 
#define Pin 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(Count,Pin,NEO_GRB + NEO_KHZ800);

const int buttonPin = 5;    // the number of the pushbutton pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

#define Brightness 10 //Set brightness to 1/10th
#define Full (255/Brightness)


void CandyCane  (int sets,int width,int wait) { //Create scrolling red and white candy cane stripes.

  //Try adjusting the width in pixels for various results.
  //Value "sets" should evenly divide into strand length

  int L;
  for(int j=0;j<(sets*width);j++) {
    for(int i=0;i< strip.numPixels();i++) {
      L=strip.numPixels()-i-1;
      if ( ((i+j) % (width*2) )<width)
        strip.setPixelColor(L,0, 128,0);
      else
        strip.setPixelColor(L, 128, 128, 128);
    };
    strip.show();
    delay(wait);
  };
};

void Wreath  (int sets,int width,int wait) { //Create scrolling red and green candy cane stripes.

  //Try adjusting the width in pixels for various results.
  //Value "sets" should evenly divide into strand length

  int L;
  for(int j=0;j<(sets*width);j++) {
    for(int i=0;i< strip.numPixels();i++) {
      L=strip.numPixels()-i-1;
      if ( ((i+j) % (width*2) )<width)
        strip.setPixelColor(L, 128, 0, 0);
      else
        strip.setPixelColor(L, 0, 128, 0);
    };
    strip.show();
    delay(wait);
  };
};

void ShootingStar  (int sets,int width,int wait) {
  int L;
  for(int j=0;j<(sets*width);j++) {
    for(int i=0;i< strip.numPixels();i++) {
      L=strip.numPixels()-i-1;
      if ( ((i+j) % (width*2) )<width)
        strip.setPixelColor(L, 128, 128, 128);
      else
        strip.setPixelColor(L, 0, 0, 0);
    };
    strip.show();
    delay(wait);
  };
};
 

void RandomWhite (int sets, int wait) { //Create sets of random white or gray pixels
  int V,i,j;
  for (i=0;i<sets;i++) {
    for(j=0;j<strip.numPixels();j++) {
      V=random(Full);
      strip.setPixelColor(j,V,V,V);
    }
    strip.show();
    delay(wait);
  }
};

void RandomColor (int sets, int wait) { //Create sets of random colors
  int i,j;
  for (i=0;i<sets;i++) {
    for(j=0;j<strip.numPixels();j++) {
      strip.setPixelColor(j,random(255)/Brightness,random(255)/Brightness,random(255)/Brightness);
    }
    strip.show();
    delay(wait);
  }
};

void RainbowStripe (int sets,int width,int wait) {
  int L;
  for(int j=0;j<(sets*width*6);j++) {
    for(int i=0;i< strip.numPixels();i++) {
      L=strip.numPixels()-i-1;
      switch ( ( (i+j)/width) % 6 ) {
        case 0: strip.setPixelColor(L,Full,0,0);break;//Red
        case 1: strip.setPixelColor(L,Full,Full,0);break;//Yellow
        case 2: strip.setPixelColor(L,0,Full,0);break;//Green
        case 3: strip.setPixelColor(L,0,Full,Full);break;//Cyan
        case 4: strip.setPixelColor(L,0,0,Full);break;//Blue
        case 5: strip.setPixelColor(L,Full,0,Full);break;//Magenta
//        default: strip.setPixelColor(L,0,0,0);//Use for debugging only
      }
    };
    strip.show();
    delay(wait);
  };
};


void colorWipe(uint32_t c, uint8_t wait) { // Fill the dots one after the other with a color
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
  Serial.print("Blue");
  Serial.print("\n");  
}
 
void RainbowCycle(uint8_t sets, uint8_t wait) {
  uint16_t i, j;
  for(j=0; j<256*sets; j++) { //cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(strip.numPixels()-i-1, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
 


uint32_t Wheel(byte WheelPos) { // The colours are a transition r - g - b - back to r.
  if(WheelPos < 85) {
   return strip.Color((WheelPos * 3)/Brightness, (255 - WheelPos * 3)/Brightness, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color((255 - WheelPos * 3)/Brightness, 0, (WheelPos * 3)/Brightness);
  } else {
   WheelPos -= 170;
   return strip.Color(0,(WheelPos * 3)/Brightness, (255 - WheelPos * 3)/Brightness);
  }
}

void chase(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels()+4; i++) {
      strip.setPixelColor(i  , c); // Draw new pixel
      strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
      strip.show();
      delay(25);
  }
}

int animRedChaseWipe(){
  colorWipe(strip.Color(0, 255, 0), 50); // Red
  chase(0x00FF00); // Red
  chase(0x00FF00); // Red
  chase(0x00FF00); // Red
}
int animGreenChaseWipe(){
  colorWipe(strip.Color(255, 0, 0), 50); // Green
  chase(0xFF0000); // Green
  chase(0xFF0000); // Green
  chase(0xFF0000); // Green
}
  
int animBlueChaseWipe(){
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
  chase(0x0000FF); // Blue
  chase(0x0000FF); // Blue
  chase(0x0000FF); // Blue
}

int pushbutton(){
  
int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button 
  // (i.e. the input went from LOW to HIGH),  and you've waited 
  // long enough since the last press to ignore any noise:  

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only animate the LEDS if the new button state is HIGH
      if (buttonState == HIGH) {
        //animation();

      }
    }
  }
  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
}
 
void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  randomSeed(1234);//Set up random number generator
  
  pinMode(buttonPin, INPUT);
  //Serial.begin(9600);
  
}
 
void loop() {
  
  chase(0xFFFFFF); // White
  chase(0xFFFFFF); // White
  chase(0xFFFFFF); // White
  chase(0xFFFFFF); // White
  chase(0xFFFFFF); // White
  
  Wreath(30,5,500);
  Wreath(30,5,500);
  
  RainbowCycle(10,2);//10 rainbow cycles
  RandomWhite(150,200);//50 sets of random grayscale
  
  animRedChaseWipe();
  animGreenChaseWipe();
  animBlueChaseWipe();
  
  RandomWhite(150,200);//50 sets of random grayscale
  RainbowCycle(10,2);//10 rainbow cycles
  
  CandyCane(30,5,250);//30 sets, 8 pixels wide, 50us delay
  CandyCane(30,5,250);//30 sets, 8 pixels wide, 50us delay
  
  animBlueChaseWipe();
  animGreenChaseWipe();
  animRedChaseWipe();
  
  RainbowCycle(10,2);//10 rainbow cycles

}



#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>

#include "RGB.h"

#define PIN 1

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
NEO_MATRIX_ROWS    + NEO_MATRIX_PROGRESSIVE,
NEO_GRB            + NEO_KHZ800);

// Set an initial brightness (used later in the flash() function)
int initialBrightness = 20;

void setup() {
  matrix.begin();
  matrix.setBrightness(initialBrightness);
}

void loop() {
  // Fill the screen with white pixels
  matrix.fillScreen(matrix.Color(white.r, white.g, white.b));
  matrix.show();
  
  // Draw the MessageBird logo
  drawLogo();
  delay(3000);
  
  // PARTY TIME!!
  flash(initialBrightness, 40, 8, 75);
}

// Flash the screen from fromBrightness to toBrightness for times amount of times
void flash(int fromBrightness, int toBrightness, int times, int wait) {
  for (int i = 0; i < (times * 2); i++)
  {
    if (i & 1) {
      matrix.setBrightness(toBrightness);
    } else {
      matrix.setBrightness(fromBrightness);
    }
    matrix.show();
    delay(wait);
  }
  
  // Reset the brightness to the initial value
  matrix.setBrightness(initialBrightness);
  matrix.show();
}

// Fade pixel (x, y) from startColor to endColor
void fadePixel(int x, int y, RGB startColor, RGB endColor, int steps, int wait) {
  for(int i = 0; i <= steps; i++) 
  {
     int newR = startColor.r + (endColor.r - startColor.r) * i / steps;
     int newG = startColor.g + (endColor.g - startColor.g) * i / steps;
     int newB = startColor.b + (endColor.b - startColor.b) * i / steps;
     
     matrix.drawPixel(x, y, matrix.Color(newR, newG, newB));
     matrix.show();
     delay(wait);
  }
}

void drawLogo() {
  // This 8x8 array represents the LED matrix pixels. 
  // A value of 1 means we’ll fade the pixel to messagebirdblue
  int logo[8][8] = {  
   {1, 1, 1, 1, 1, 1, 0, 0},
   {0, 0, 0, 0, 1, 1, 0, 0},
   {1, 1, 1, 1, 1, 0, 1, 1},
   {0, 0, 0, 1, 1, 0, 1, 0},
   {0, 1, 1, 1, 0, 1, 1, 0},
   {0, 0, 0, 1, 1, 1, 1, 0},
   {0, 0, 1, 1, 1, 1, 0, 0},
   {0, 1, 1, 1, 1, 0, 0, 0}
  };
   
  for(int row = 0; row < 8; row++) {
    for(int column = 0; column < 8; column++) {
     if(logo[row][column] == 1) {
       fadePixel(column, row, white, messagebirdblue, 40, 0);
     }
   }
  }
}

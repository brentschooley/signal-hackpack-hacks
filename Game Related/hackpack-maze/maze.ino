// Maze bouncer
// By JeanCarl Bisson (@dothewww)
 
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include "RGB.h"
 
#define PIN 1
 
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);
 
  // 0 is a path, 1 is a wall, 2 is where the cursor starts/is
   
  int grid[8][8] = {  
   {1, 1, 1, 1, 1, 1, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 1, 1, 1, 1, 1, 1},
   {1, 0, 1, 0, 0, 0, 1, 2},
   {1, 0, 1, 0, 1, 0, 1, 0},
   {1, 0, 1, 0, 1, 0, 1, 0},
   {1, 0, 0, 0, 1, 0, 0, 0},
   {1, 1, 1, 1, 1, 1, 1, 1}
  };
  
void setup() {
  matrix.begin();
  matrix.setBrightness(30);
  matrix.setTextColor( matrix.Color(255, 255, 255) );
  matrix.setTextWrap(false);
}
 
void loop() {
  drawMatrix();
  delay(50);
  movePeg();
}
 
 
void movePeg() {
  // This 8x8 array represents the LED matrix pixels. 
  // A value of 1 means we’ll fade the pixel to white
 
   
  for(int row = 0; row < 8; row++) {
    for(int column = 0; column < 8; column++) {
      
     if(grid[row][column] == 2) {
      // Brute force for the win!!!!! Who needs to be efficient!
      int randomDirection = rand()%4;
      
      // Go down
      if(randomDirection == 0 && row < 7 && grid[row+1][column] == 0)
      {
        grid[row][column] = 0;
        grid[row+1][column] = 2;
        return;
      }
 
      // Go right
      if(randomDirection == 1 && column < 7 && grid[row][column+1] == 0)
      {
        grid[row][column] = 0;
        grid[row][column+1] = 2;
        return;
      }
 
      // Go left
      if(randomDirection == 2 && column > 0 && grid[row][column-1] == 0)
      {
        grid[row][column] = 0;
        grid[row][column-1] = 2;
        return;
      }     
 
      // Go up
      if(randomDirection == 3 && row > 0 && grid[row-1][column] == 0)
      {
        grid[row][column] = 0;
        grid[row-1][column] = 2;
        return;
      }          
     }
   }
  }
 
  matrix.show();
}
 
void drawMatrix() {
  for(int row = 0; row < 8; row++) {
    for(int column = 0; column < 8; column++) {
      
     if(grid[row][column] == 0) {
       matrix.drawPixel(column, row, matrix.Color(off.r, off.g, off.b));
     }
      
     if(grid[row][column] == 1) {
       matrix.drawPixel(column, row, matrix.Color(red.r, red.g, red.b));
     }
 
     if(grid[row][column] == 2) {
       matrix.drawPixel(column, row, matrix.Color(white.r, white.g, white.b));
     }     
   }
  }
 
  matrix.show();
}

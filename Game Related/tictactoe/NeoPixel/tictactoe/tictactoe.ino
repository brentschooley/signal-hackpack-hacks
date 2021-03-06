/******************************************************************************
Marie Huynh
May 12, 2015
Twilio Signal Developer Conference for Communications

This short program plays tic-tac-toe with itself on an 8x8 Adafruit Neopixel 
RGB LED Matrix.  The "AI" really just picks a random free spot until the win
condition is satisfied or it's a tie.
******************************************************************************/

#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include "RGB.h"

#define PIN 1

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP    + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

// Internal representation of the game
int gameboard[3][3] = {
  {0,0,0},
  {0,0,0},
  {0,0,0}
};

void setup() {
  matrix.begin();
  matrix.setBrightness(20);
  matrix.setTextColor( matrix.Color(white.r, white.g, white.b) );
  matrix.setTextWrap(false);

  // Title
  String ttt = "TicTacToe";
  scrollText(ttt);
  delay(500);
}

void loop() {
  // Set up blank board
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      fadePixel(i, j, off, off, 30, 0);
    }
  }
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      gameboard[i][j] = 0;
    }
  }
  
  // Print grid
  drawGrid();
  
  // Play 9 rounds
  int x,y;
  
  for(int i = 0; i < 9; i++){
    // Pick new spot
    do {
      x = random(0,3);
      y = random(0,3);
    } while (gameboard[x][y] != 0);

    // Set internal gameboard state
    gameboard[x][y] = (i%2) + 1;

    // Update display
    displayMove(x,y,(i%2)+1); 
  
    // If win, end and display
    if(checkDisplayWin())
      break;

    delay(500);
  }
}

// Check for satisfaction of win condition
int checkDisplayWin() {
  // Check horizontal and verticals
  for(uint16_t i=0; i < 3; i++) {
    if(gameboard[i][0] > 0 &&   //
      gameboard[i][0] == gameboard[i][1] && 
      gameboard[i][0] == gameboard[i][2]) {
        displaywin(gameboard[i][0]);
        return 1;
    } else if(gameboard[0][i] > 0 && 
      gameboard[0][i] == gameboard[1][i] && 
      gameboard[0][i] == gameboard[2][i]) {
        displaywin(gameboard[0][i]);
        return 1; 
    }
  }

  // Check diagonals
  if(gameboard[0][0] > 0 &&  
    gameboard[0][0] == gameboard[1][1] && 
    gameboard[0][0] == gameboard[2][2]) {
      displaywin(gameboard[0][0]);
      return 1; 
  }else if(gameboard[0][2] > 0 && 
    gameboard[0][2] == gameboard[1][1] && 
    gameboard[1][1] == gameboard[2][0]) {
      displaywin(gameboard[0][0]);
      return 1; 
  }
  return 0; // Nope, keep playing
}

// Display winning text
// TODO: add player info/animation
void displaywin(int winner) {
  delay(1000);
  String winnertext = "Win!";
  scrollText(winnertext);
}

//draw grid
void drawGrid(){
  // This 8x8 array represents the LED matrix pixels. 
  // A value of 1 means we’ll fade the pixel to white
  int logo[8][8] = {  
   {0, 0, 1, 0, 0, 1, 0, 0},
   {0, 0, 1, 0, 0, 1, 0, 0},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {0, 0, 1, 0, 0, 1, 0, 0},
   {0, 0, 1, 0, 0, 1, 0, 0},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {0, 0, 1, 0, 0, 1, 0, 0},
   {0, 0, 1, 0, 0, 1, 0, 0}
  };
   
  for(int row = 0; row < 8; row++) {
    for(int column = 0; column < 8; column++) {
      if(logo[row][column] == 1) {
        fadePixel(column, row, purple, white, 30, 0);
      }
    }
  } 
}

// Display the chosen location
void displayMove(int x, int y, int player){
  for(int row = x*3; row < (x*3)+2; row++) {
    for(int column = y*3; column < (y*3)+2; column++) {
      if(player < 2) {
        fadePixel(column, row, off, teal, 30, 0);
      }else{
        fadePixel(column, row, off, orange, 30, 0);
      }
    }
  }
}

// Fill the dots one after the other with a color
void animation(RGB color, uint8_t wait) {
  for(uint16_t row=0; row < 8; row++) {
    for(uint16_t column=0; column < 8; column++) {
      matrix.drawPixel(column, row, matrix.Color(color.r, color.g, color.b));
      matrix.show();
      delay(wait);
    }
  }
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

// Scroll text to the left
void scrollText(String textToDisplay) {
  int x = matrix.width();
  int pixelsInText = textToDisplay.length() * 7;
  
  matrix.setCursor(x, 0);
  matrix.print(textToDisplay);
  matrix.show();
  
  while(x > (matrix.width() - pixelsInText)) {
    matrix.fillScreen(matrix.Color(teal.r, teal.g, teal.b));
    matrix.setCursor(--x, 0);
    matrix.print(textToDisplay);
    matrix.show();
    delay(150);
  }
}

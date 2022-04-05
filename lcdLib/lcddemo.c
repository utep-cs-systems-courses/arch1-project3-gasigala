/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLUE);

  drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);

  fillRectangle(30,30, 60, 60, COLOR_ORANGE);

  int a =0, lenght =20;
  int fCol = 50, fRow = 50;
  /*  for(int i =0 ; i < 10; i++){
    drawPixel(fCol +col, fRow +row, COLOR_WHITE);
    drawPixel(fCol -col, fRow -row, COLOR_GREEN);
    col++;
    row++;
    }*/
  for(a =0 ;a< lenght; a++){
    drawPixel(fCol +a, fRow +a, COLOR_BLUE);
    drawPixel(fCol +a, fRow, COLOR_PURPLE);
    drawPixel(fCol +lenght, fRow + a, COLOR_WHITE);

    if(a%2 ==1){
      for(int v =0 ; v < a; v++){
	drawPixel(fCol +a, fRow + v, COLOR_PINK);
	drawPixel(fCol +v, fRow + a, COLOR_RED);
      }
    }
  }
  trapezoid();
}

void triangle(){
  clearScreen(COLOR_BLUE);
  int a =0, lenght =20;
  int fCol = 50, fRow = 50;
  
  
  for(a =0 ;a< lenght; a++){
    drawPixel(fCol +a, fRow +a, COLOR_RED);
    drawPixel(fCol +a, fRow, COLOR_PURPLE);
    drawPixel(fCol +lenght, fRow + a, COLOR_WHITE);
  }
}

void square(){
  clearScreen(COLOR_BLUE);
  int a =0, lenght =20;
  int fCol = 50, fRow = 50;

  for(a =0 ;a< lenght; a++){
    drawPixel(fCol , fRow +a, COLOR_RED);//left side
    drawPixel(fCol +a, fRow, COLOR_PURPLE);//top
    drawPixel(fCol +lenght, fRow + a, COLOR_WHITE);//right side
    drawPixel(fCol +a, fRow +lenght , COLOR_GREEN);
  }
}

    
void trapezoid(){
  //two triangles and a square
  clearScreen(COLOR_BLUE);
  int a =0, lenght =20;
  int fCol = 50, fRow = 75;//well start on a lower part of the screen
  for(a =0 ;a< lenght; a++){
    drawPixel(fCol +a, fRow +a, COLOR_RED);
    drawPixel(fCol +a, fRow, COLOR_PURPLE);
    drawPixel(fCol +lenght, fRow + a, COLOR_WHITE);
  }
  
  fRow = fRow - lenght;
  for(a =0 ;a< lenght; a++){
    drawPixel(fCol , fRow +a, COLOR_RED);//left side                                                    
    drawPixel(fCol +a, fRow, COLOR_PURPLE);//top                                                        
    drawPixel(fCol +lenght, fRow + a, COLOR_WHITE);//right side                                         
    drawPixel(fCol +a, fRow +lenght , COLOR_GREEN);//bottom side
  }
  
  // we dont mess with the row since we will be decrementing this time 
  for(a =0 ;a< lenght; a++){
    drawPixel(fCol +a, fRow -a, COLOR_RED);
    drawPixel(fCol +a, fRow, COLOR_PURPLE);
    drawPixel(fCol +lenght, fRow - a, COLOR_WHITE);
  }
}

  

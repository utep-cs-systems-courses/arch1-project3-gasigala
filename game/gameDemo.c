#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"
/*
char
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  // update 
  P2IES |= SWITCHES;
  P2IES |= (p2val & SWITCHES);  /* if switch up, sense down 
  P2IES &= (p2val | ~SWITCHES); /* if switch down, sense up 
  return p2val;
}
*/

void
switch_init()                   /* setup switch */
{
  P2REN |= SWITCHES;            /* enables resistors for switches */
  P2IE |= SWITCHES;             /* enable interrupts from switches */
  P2OUT |= SWITCHES;            /* pull-ups for s  P2OUT |= SWITCHES;*/
  P2DIR &= ~SWITCHES;           /* set switches' bits for input */
  switch_update_interrupt_sense();
}

int switches = 0;

/*
void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  switches = ~p2val & SWITCHES;
}
*/


short drawPos[2] = {10,10}, controlPos[2] = {10,10};
short velocity[2] = {3,8}, limits[2] = {screenWidth-36, screenHeight-8};

short redrawScreen = 1;
u_int controlFontColor = COLOR_GREEN;

void wdt_c_handler()
{
  static int secCount = 0;

  secCount ++;
  if (secCount >= 500) {		// 10/sec
    secCount = 0;
    redrawScreen = 1;
  }
}

void update_shape();
void draw_eye(int fCol, int frow);
void draw_sun();
void draw_background();
void draw_background2();
int jump_table(int sw);

void main()
{
  
  P1DIR |= LED;		/**< Green led on when CPU on */
  P1OUT |= LED;
  configureClocks();
  lcd_init();
  switch_init();
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  //clearScreen(COLOR_SKY_BLUE);
  draw_background();
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      update_shape();
    }
    P1OUT &= ~LED;	/* led off */
    or_sr(0x10);	/**< CPU OFF */
    P1OUT |= LED;	/* led on */
  }
}

int sw = 0;
int current_state = 0;
int fRow = 50;
int fCol = 50;


//im gonna add 
int jumpTable(int sw) {
  switch (sw) {
  case 1:
    break;
  case 2:
    break;
  case 3:
    break;
  default:
    break;
  }
}


void
update_shape()
{
  int four = switches & SW4;
  int one = switches & SW1;
  int two = switches & SW2;
  int three = switches & SW3;

  if (one){
    if(current_state != sw){
      draw_background();
      //draw_eye(50, 50);
      current_state = 1;
    }
    sw = 1;
  }
  if (two){
    if(current_state != sw){
      draw_background2();
      current_state = 2;
    }
    sw = 2;
  }
  if (three)
    sw = 3;
  if (four) {
    sw = 4;
    drawString5x7(4,100, "AHHHHH", COLOR_WHITE, COLOR_BLUE);
  }

  jumpTable(sw);
  //sw =0;
  for (int i = 0; i < 10; i++) {
    fRow += 10;
    draw_eye(fCol, fRow);
    if(fRow >= screenHeight){
      fRow = 50;
    }
    //updateLocations();
    }
}


void
draw_eye(int fCol, int fRow){
  // clearScreen(COLOR_WHITE);
  fillRectangle(fCol -12, fRow-12, 48, 48, COLOR_SKY_BLUE);
  int a =0,  lenght = 24;
  int i = 12;
  int j = 0;
  for( a =0; a < lenght; a++){
    //draw previous position as sky_blue
    drawPixel(fCol+ a, fRow-10, COLOR_SKY_BLUE);
    drawPixel(fCol+a, fRow+1-10, COLOR_SKY_BLUE);
    //top line of eye
    drawPixel(fCol+ a, fRow, COLOR_BLACK);
    drawPixel(fCol+a, fRow+1, COLOR_RED);
    // draw previous position as sky blue
    drawPixel(fCol +a, fRow+ lenght+1-10, COLOR_SKY_BLUE);
    drawPixel(fCol+a, fRow+ lenght-10, COLOR_SKY_BLUE);
    //botom line of eye
    drawPixel(fCol +a, fRow+ lenght+1, COLOR_BLACK);
    drawPixel(fCol+a, fRow+ lenght, COLOR_RED);
  }
  //slanted lines
  for( a =0; a<lenght/2; a++){
    //top left 
    drawPixel(fCol - j , fRow + j-10, COLOR_SKY_BLUE);
    drawPixel(fCol - j , fRow + j, COLOR_BLACK);
    //bottom left
    drawPixel(fCol - i  , fRow - i +lenght-10 , COLOR_SKY_BLUE);
    drawPixel(fCol - i  , fRow - i +lenght , COLOR_BLACK);
    //top right
    drawPixel(fCol+ lenght +j, fRow + j- 10, COLOR_SKY_BLUE);
    drawPixel(fCol+ lenght +j, fRow + j, COLOR_BLACK);
    //bottom right
    drawPixel(fCol + lenght +j, fRow + lenght - j-10, COLOR_SKY_BLUE);
    drawPixel(fCol + lenght +j, fRow + lenght - j, COLOR_BLACK); 
    i--;
    j++;
  }
  //middle part of the eye
    for(a =0; a < 8; a++){
    for(int b =0 ; b < 8; b++){
      drawPixel(fCol + 8 + a, fRow +8 +b, COLOR_BLACK);
    }
  }
    /*    
  for(a =0; a < 8; a++){
    for(int b =0 ; b < 8; b++){
      drawPixel(fCol + 8 + a, fRow + 8+ b, COLOR_BLUE);
    }
  }
    */
}

void
draw_sun(){
  int subtract = 28;
  for( int a = 0 ; a < 28; a++){
    for( int b = 0; b < 28; b++){
      if( b <= subtract){
	drawPixel( a, b, COLOR_BLACK);
      }
    }
    //this adds the variation
    subtract -= a  % 4;
  }
}

void
draw_background(){
  clearScreen(COLOR_SKY_BLUE); 
  draw_sun();
  //fillRectangle(0, 80, 128, 160/2, COLOR_ORANGE_RED);
  //this makes the road marks in screen one
  /* for(int a = 0; a < 128; a+=24){
    for(int b =0; b <8; b++){
      drawPixel(a+ b, 160 - 160/4, COLOR_BLACK);
      drawPixel(a+b, (160 - 160/4)+ 1, COLOR_BLACK);
      drawPixel(a+b, (160 - 160/4)+ 2, COLOR_BLACK);
      drawPixel(a+b, (160 - 160/4)+ 3, COLOR_BLACK);
    }
  }
  if(sw == 1){
    drawString5x7(4,100, "one", COLOR_WHITE, COLOR_BLUE);
  }
  else if(sw == 2){
    drawString5x7(4, 100, "two", COLOR_WHITE, COLOR_BLUE);
  }
  */
}
  

void
draw_background2(){
  clearScreen(COLOR_SKY_BLUE);
  // fillRectangle(0, 80, 128, 160/2, COLOR_ORANGE_RED);
  for(int a = 24; a< 32; a++){
    for ( int b = 50; b < 120; b++){
      drawPixel(a, b, COLOR_BLACK);
      drawPixel(a +70, b, COLOR_BLACK);
    }
  }
  for (int a =0; a < 70; a++){
    drawPixel(a +24, 50, COLOR_BLACK);
    drawPixel(a +24, 51, COLOR_BLACK);
    drawPixel(a +24, 51, COLOR_BLACK);
    drawPixel(a +24, 51, COLOR_BLACK);
  }
}


void
draw_door(){
  
}

void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}

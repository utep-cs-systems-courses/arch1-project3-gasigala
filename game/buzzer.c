#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "buzzer_notes.h"
 
void buzzer_init()
{
    /* 
       Direct timer A output "TA0.1" to P2.6.  
        According to table 21 from data sheet:
          P2SEL2.6, P2SEL2.7, anmd P2SEL.7 must be zero
          P2SEL.6 must be 1
        Also: P2.6 direction must be output
    */
    timerAUpmode();		/* used to drive speaker */
    P2SEL2 &= ~(BIT6 | BIT7);
    P2SEL &= ~BIT7; 
    P2SEL |= BIT6;
    P2DIR = BIT6;		/* enable output to speaker (P2.6) */
}

void buzzer_set_period(short cycles) /* buzzer clock = 2MHz.  (period of 1k results in 2kHz tone) */
{
  CCR0 = cycles; 
  CCR1 = cycles >> 1;		/* one half cycle */
}

void buzzer_stop()
{
  buzzer_set_period(0);
}


void play_song_1()
{
  static char curr_note = 0;
  static int  ledBool =0;
  // All notes of song, 0s are for break in between notes
  int notes[47] = {D5, A4, D5, A4, D5, A4, D5, B4_FLAT, D5, B4_FLAT, D5, B4_FLAT, D5, B4_FLAT,A4, A3, D4, C4_SHARP, D4, E4, F4_SHARP, D4, D4, C4_SHARP, C4_SHARP, B3, D4, D4, D4, E4, D4, D4, D4, 0, 0, G4, G4, F4_SHARP, D4, D4, D4, A3, D4, C4_SHARP, D4, E4, F4_SHARP };
  int n = 47;

  if (curr_note < n){
      buzzer_set_period(notes[curr_note]);
      curr_note++;
  }
  else {
    curr_note = 0;
  }
  
}

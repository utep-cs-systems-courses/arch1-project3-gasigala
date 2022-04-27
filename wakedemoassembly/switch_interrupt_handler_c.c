#include "switches.h"
void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  switches = ~p2val & SWITCHES;
}


char
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);  /* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES); /* if switch down, sense up */
  return p2val;

}

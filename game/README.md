# Game demo

## Gregorio Sigala

This is basically a pretty simple state machine that will respond to the button inputs. The big idea is that we will keep track of the state while the program runs then update the button accordingly.
The two main states  correspond to S1 and S2. When in these states we will call **draw_background** and **draw_background2** respectively. These color the screen. We will then call **draw_eye**. 
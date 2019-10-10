/** @file   game.c
    @authors Evan Oijordsbakken, Ryan Miller
    @date   09 October 2019

    This file runs the main program of the PSR game
    for the UCFK for Assignment
*/

 #include "system.h"
 #include "pacer.h"
 #include "ir_uart.h"
 #include "mydisplay.h"
 #include "mytasks.h"

#define PACER_RATE 500
#define MESSAGE_RATE 25

int main(void)
{
  system_init();
  ir_uart_init ();
  pacer_init(PACER_RATE);
  screen_init(PACER_RATE, MESSAGE_RATE);

  startup_task();

  int again = ready_task();

  while (again) {
    int p1_score = 0;
    int p2_score = 0;

    while (p1_score < 2 && p2_score < 2) {

      int win = round_task();

      if (win == 1) {
        p1_score++;

      } else if (win == 0) {
        p2_score++;
      }
    }

    if (p1_score == 2) {
      final_msg_task(1);

    } else {
      final_msg_task(0);
    }

    again = ready_task();
  }
  clear();
}

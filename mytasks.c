/** @file   mytasks.c
    @author Evan Oijordsbakken, Ryan Miller
    @date   09 October 2019

    This module implements the main sections of the PSR game
    for the UCFK for Assignment
*/

#include "system.h"
#include "mytasks.h"
#include "mydisplay.h"
#include "navswitch.h"
#include "mytaskhelpers.h"


/* Runs task to show beginning titles */
void startup_task(void)
{
  set_message("Paper Scissors Rock first to 2 ");

  int cont = 0;

  while (!cont) {
    update_all();

    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
      cont = 1;
    }
  }
}


/* Runs task to check player readyness */
/* Returns 0 if stop playing, 1 if play again */
int ready_task(void)
{
  int cont = 0;
  int again = 0;
  char char1 = 'Y';
  int rdy1 = 3; //Arbitrary default
  int rdy2 = 3;

  while (!cont) {
    update_all();
    display_character(char1);

    char1 = ready_switch(char1);
    rdy1 = ready_select(char1, rdy1);
    rdy2 = check_ready(rdy2);

    if (rdy1 == 1 && rdy2 == 1) {
      cont = 1;
      again = 1;
    } else if (rdy1 == 0 && rdy2 == 0) {
      cont = 1;
    }
  }

  return again;
}


/* Runs task to play a round of PSR */
/* Returns 1 if player1 wins, 0 if player2 wins, 3 if draw */
int round_task(void)
{
  char p1_sign = sign_select();
  char p2_sign = sign_receive();
  char result = round_result(p1_sign, p2_sign);

  int win = 3;
  if (result == 'W') {
    win = 1;
  } else if (result == 'L') {
    win = 0;
  }

  display_character(result);

  while(!navswitch_push_event_p(NAVSWITCH_PUSH)) {
    update_all();
  }

  return win;
}


/* Runs task to display final message */
/* Takes 1 if player1 won the match, 0 if player2 won the match*/
void final_msg_task(int winner)
{
  int cont = 0;

  if (winner == 1) {
    set_message("You WON!! Play again? ");

  } else {
    set_message("You LOST :( Play again? ");
  }

  while (!cont) {
    update_all();

    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
      cont = 1;
    }
  }
}

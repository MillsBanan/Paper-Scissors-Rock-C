/** @file   mytaskhelpers.c
    @author Evan Oijordsbakken, Ryan Miller
    @date   09 October 2019

    This module holds the functions required by the tasks
    for the PSR game
*/

#include "system.h"
#include "pacer.h"
#include "ir_uart.h"
#include "mydisplay.h"
#include "navswitch.h"


// all tasks

/* Runs new round of task */
void update_all(void)
{
  pacer_wait();
  screen_update();
  navswitch_update();
}


// ready task

/* Scrolls through ready/not ready options */
char ready_switch(char char1)
{
  if (navswitch_push_event_p(NAVSWITCH_EAST) || navswitch_push_event_p(NAVSWITCH_WEST)) {
    if (char1 == 'Y') {
      char1 = 'N';
    } else {
      char1 = 'Y';
    }
  }

  return char1;
}

/* Allows player to select ready/not ready */
int ready_select(char char1, int rdy1)
{
  if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
    ir_uart_putc(char1);
    rdy1 = 0;
    if (char1 == 'Y') {
      rdy1 = 1;
    }
  }

  return rdy1;
}

/* Checks if other player is ready */
int check_ready(int rdy2)
{
  if (ir_uart_read_ready_p()) {
    char char2 = ir_uart_getc();
    rdy2 = 0;
    if (char2 == 'Y') {
      rdy2 = 1;
    }
  }

  return rdy2;
}


// round task

/* Lets player1 choose their sign */
char sign_select(void)
{
  int signs_index = 0;
  int cont = 0;
  char signs[3] = {'P', 'S', 'R'};

  while (!cont) {
    update_all();
    display_character(signs[signs_index]);

    if (navswitch_push_event_p(NAVSWITCH_EAST)) {
      if (signs_index == 2) {
        signs_index = 0;
      } else {
        signs_index++;
      }
    } else if (navswitch_push_event_p(NAVSWITCH_WEST)) {
      if (signs_index == 0) {
        signs_index = 2;
      } else {
        signs_index--;
      }
    }

    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
      cont = 1;
    }
  }

  ir_uart_putc(signs[signs_index]);
  return signs[signs_index];
}

/* Waits to receive player2's sign */
char sign_receive(void)
{
  int cont = 0;
  int p2_sign = ' ';

  while (!cont) {
    pacer_wait();

    if (ir_uart_read_ready_p()) {
      p2_sign = ir_uart_getc();
      cont = 1;
    }
  }

  return p2_sign;
}

/* Compares player signs and determines winner */
char round_result(char p1_sign, char p2_sign)
{
  char outcome = ' ';

  if (p1_sign == p2_sign) {
      outcome = 'D';
  } else if (p1_sign == 'P' && p2_sign == 'R') {
      outcome = 'W';
  } else if (p1_sign == 'R' && p2_sign == 'S') {
      outcome = 'W';
  } else if (p1_sign == 'S' && p2_sign == 'P') {
      outcome = 'W';
  } else {
      outcome = 'L';
  }

  return outcome;
}

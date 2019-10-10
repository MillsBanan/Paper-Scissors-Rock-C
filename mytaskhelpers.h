/** @file   mytaskhelpers.h
    @author Evan Oijordsbakken, Ryan Miller
    @date   09 October 2019

    This module holds the functions required by the tasks
    for the PSR game
*/

#ifndef MYTASKHELPERS_H
#define MYTASKHELPERS_H

#include "system.h"

// all tasks

/* Runs new round of task */
void update_all(void);


// ready task

/* Scrolls through ready/not ready options */
char ready_switch(char char1);

/* Allows player to select ready/not ready */
int ready_select(char char1, int rdy1);

/* Checks if other player is ready */
int check_ready(int rdy2);


// round task

/* Lets player1 choose their sign */
char sign_select(void);

/* Waits to receive player2's sign */
char sign_receive(void);

/* Compares player signs and determines winner */
char round_result(char p1_sign, char p2_sign);

#endif

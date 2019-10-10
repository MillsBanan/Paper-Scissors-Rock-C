/** @file   mytasks.h
    @author Evan Oijordsbakken, Ryan Miller
    @date   09 October 2019

    This module implements the main sections of the PSR game
    for the UCFK for Assignment
*/
#ifndef MYTASKS_H
#define MYTASKS_H

#include "system.h"

/* Runs task to show beginning titles */
void startup_task(void);

/* Runs task to check player readyness */
/* Returns 0 if stop playing, 1 if play again */
int ready_task(void);

/* Runs task to play a round of PSR */
/* Returns 1 if player1 wins, 0 if player2 wins, 3 if draw */
int round_task(void);

/* Runs task to display final message */
/* Takes 1 if player1 won the match, 0 if player2 won the match*/
void final_msg_task(int winner);

/* Clears display at end of game */
void clear(void);

#endif

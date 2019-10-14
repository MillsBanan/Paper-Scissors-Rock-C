/** @file     round.h
    @authors  Evan Oijordsbakken, Ryan Miller
    @date     15 October 2019
    @brief    Ready check

    This module implements the selection and transmission of a yes or no choice,
    and the recieving of the other players choice.

*/

#ifndef READY_H
#define READY_H


/** Selects and transmits the choice of the player, changes the game state to
    'P' (play round) when both players have selected 'Y' (yes).
    @param char* pointer to variable that holds the current stage of the game.  */
void ready_task(char* stage);


#endif

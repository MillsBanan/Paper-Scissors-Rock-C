/** @file     round.h
    @authors  Evan Oijordsbakken, Ryan Miller
    @date     15 October 2019
    @brief    Handles each round

    This module implements sign selection, sign transmitting/ recieving and
    the playing of each round.
*/


#ifndef ROUND_H
#define ROUND_H


/** Plays a round of paper scissors rock, changes the state of the game to the
    respective outcome of the round for each player - ('W', 'L', 'D').
    @param char* stage pointer to variable that holds the current stage of the game.  */
void round_task(char* stage);


#endif

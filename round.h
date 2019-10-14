/** @file round.h
    @authors Evan Oijordsbakken, Ryan Miller
    @date   10 October 2019
    @brief Handles each round

    This module implements sign selection, sign transmitting/ recieving and
    the playing of each round.
*/
#ifndef ROUND_H
#define ROUND_H


/** Allows the player to select a sign using the navswitch
    @param p1_sign variable to hold the sign selected by the player.  */
void sign_select(char* p1_sign);


/** Polls the IR reciever, assigns the recieved sign to p2_sign if valid
    @param p2_sign variable to hold the recieved sign from the other player.  */
void sign_recieve(char* p2_sign);


/** Determines the outcome of the round
    @param p1_sign sign selected by player one
    @param p2_sign sign selected by player two
    @return outcome of the round relative to player one.  */
char round_result(char p1_sign, char p2_sign);


/** Plays a round of paper scissors rock
    @param &stage the current stage of the game.  */
void round_task(char* stage);

#endif

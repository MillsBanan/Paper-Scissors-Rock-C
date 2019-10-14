/** @file round.h
    @authors Evan Oijordsbakken, Ryan Miller
    @date   10 October 2019
    @brief Handles each round

    This module implements sign selection, sign transmitting/ recieving and
    the playing of each round.
*/
#ifndef MESSAGES_H
#define MESSAGES_H

/** Valid signs: P = paper, S = scissors, R = rock.  */


void display_character(char character);

void display_message_once(char *message, int timing_multiplier);

void display_scores(char *scores);

#endif

/** @file     messages.h
    @authors  Evan Oijordsbakken, Ryan Miller
    @date     15 October 2019
    @brief    Module for displaying messages on the LED matrix

    This module implements the displaying of a character, a message once,
    and the current score.
*/


#ifndef MESSAGES_H
#define MESSAGES_H


/** Displays the character given as a parameter
    @param char character any ASCII character. */
void display_character(char character);


/** Displays a message once, message can be skipped via a navswitch push
    @param char *message text at most length 32 including null terminator
    - note that the text requires variable levels of padding with whitespace
    to display properly.   */
void display_message_once(char *message);


/** Displays the scores of both players while button 0 is held down
    @param char *scores variable to hold a formatted string of both players scores. */
void display_scores(char *scores);


#endif

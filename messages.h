/** @file messages.h
    @authors Evan Oijordsbakken, Ryan Miller
    @date   14 October 2019
    @brief  Module for displaying messages on the LEDmatrix

    This module implements the displaying of a character, a message, and the
    current score.
*/
#ifndef MESSAGES_H
#define MESSAGES_H

/** Displays the character given as a parameter
    @param char character any ASCII character. */
void display_character(char character);

/** Displays a message once
    @param char *message a message at most length 32 - note that the message
    usually requires some padding with whitespace on the end. */
void display_message_once(char *message);

/** Displays the scores of both players while button 0 is held down
    @param char *scores a formatted string of both players scores. */
void display_scores(char *scores);

#endif

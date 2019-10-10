/** @file   mydisplay.h
    @author Evan Oijordsbakken, Ryan Miller
    @date   09 October 2019

    This module implements helper functions for using the display screen
    of the UCFK for Assignment
*/
#ifndef MYDISPLAY_H
#define MYDISPLAY_H

#include "system.h"

/* Sets up the screen to play game*/
void screen_init(int pacer_rate, int msg_rate);

/* Sets new message to display */
void set_message(char* message);

/* Updates screen */
void screen_update(void);

/* Displays character on LED screen */
void display_character(char character);

#endif

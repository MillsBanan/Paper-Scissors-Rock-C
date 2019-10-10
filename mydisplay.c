/** @file   mydisplay.c
    @author Evan Oijordsbakken, Ryan Miller
    @date   09 October 2019

    This module implements helper functions for using the display screen
    of the UCFK for Assignment
*/

#include "system.h"
#include "tinygl.h"
#include "mydisplay.h"
#include "../fonts/font5x7_1.h"


/* Sets up the screen to play game*/
void screen_init(int pacer_rate, int msg_rate)
{
  tinygl_init (pacer_rate);
  tinygl_font_set (&font5x7_1);
  tinygl_text_speed_set (msg_rate);
  tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
}

/* Sets new message to display */
void set_message(char* message)
{
  tinygl_text(message);
}

void screen_update(void)
{
  tinygl_update();
}

/* Displays character on LED screen */
void display_character(char character)
{
  char buffer[2];
  buffer[0] = character;
  buffer[1] = '\0';
  tinygl_text (buffer);
}

/* Clears display at end of game */
void clear(void)
{
  tinygl_clear();
  tinygl_update();
}

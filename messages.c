/** @file messages.h
    @authors Evan Oijordsbakken, Ryan Miller
    @date   15 October 2019
    @brief  Module for displaying messages on the LED matrix

*/


#include "messages.h"
#include "system.h"
#include "button.h"
#include "navswitch.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include <string.h>


/** Used to calculate the number of pacer_wait calls needed
    to display a message only once
    TIMING_MULTIPLIER = 10 * (PACER_RATE / MESSAGE_RATE) */
#define TIMING_MULTIPLIER 800


/** Displays the character given as a parameter
    @param char character any ASCII character. */
void display_character(char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text(buffer);
}


/** Displays a message once, message can be skipped via a navswitch push
    @param char *message text at most length 32 including null terminator
    - note that the text requires variable levels of padding with whitespace
    to display properly.   */
void display_message_once(char *message)
{
    tinygl_text(message);

    uint16_t count = 0;
    uint16_t max_count = strlen(message) * TIMING_MULTIPLIER;

    while (count < max_count) {
        pacer_wait();
        tinygl_update();
        navswitch_update();

        count++;

        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            navswitch_update();
            break;
        }
    }
}


/** Displays the scores of both players while button 0 is held down
    @param char *scores variable to hold a formatted string of both players scores. */
void display_scores(char *scores)
{
    tinygl_text(scores);

    while (button_down_p(0)) {
        pacer_wait();
        tinygl_update();
        button_update();
    }
    navswitch_update();
}

/** @file messages.h
    @authors Evan Oijordsbakken, Ryan Miller
    @date   14 October 2019
    @brief  Module for displaying messages on the LEDmatrix

*/


#include "messages.h"
#include "system.h"
#include "button.h"
#include "navswitch.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include <string.h>


/** Used to calculate the number of pacer_wait calls to display a message once
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
    @param char *message a message at most length 32 - note that the message
    usually requires some padding with whitespace on the end. */
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
    @param char *scores a formatted string of both players scores. */
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

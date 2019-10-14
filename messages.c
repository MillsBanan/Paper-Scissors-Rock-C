/** @file round.c
    @authors Evan Oijordsbakken, Ryan Miller
    @date   10 October 2019
    @brief Handles each round

*/
#include <string.h>
#include "messages.h"
#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "navswitch.h"
#include "button.h"
#include "../fonts/font5x7_1.h"


void display_character(char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text(buffer);
}

void display_message_once(char *message, int timing_multiplier)
{
    tinygl_text(message);
    /** while (1) {
        pacer_wait();
        tinygl_update();
        navswitch_update();

        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            break;
        }
    } */

    uint16_t count = 0;
    uint16_t max_count = strlen(message) * timing_multiplier;

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

void display_scores(char *scores)
{
    tinygl_text(scores);

    while (button_down_p(0)) {
        pacer_wait();
        tinygl_update();
        button_update();
    }

}

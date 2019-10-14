/** @file round.c
    @authors Evan Oijordsbakken, Ryan Miller
    @date   10 October 2019
    @brief Handles each round

*/

#include "messages.h"
#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "navswitch.h"
#include "../fonts/font5x7_1.h"


void display_character(char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text(buffer);
}

void display_message(char *message)
{
    tinygl_text(message);
    while (1) {
        pacer_wait();
        tinygl_update();
        navswitch_update();

        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            break;
        }
    }
}

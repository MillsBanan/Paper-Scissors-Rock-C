/** @file   game.c
    @authors Evan Oijordsbakken, Ryan Miller
    @date   09 October 2019

    This file runs the main program of the PSR game
    for the UCFK for Assignment
*/
#include <string.h>
#include "system.h"
#include "pacer.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "navswitch.h"
#include "../fonts/font5x7_1.h"
#include "round.h"
#include "ready.h"
#include "messages.h"

#define PACER_RATE 1000
#define MESSAGE_RATE 25
#define MAX_SCORE 3


void startup_init(void)
{
    system_init();
    ir_uart_init ();
    pacer_init(PACER_RATE);
    tinygl_init(PACER_RATE);
    tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
}

int main(void)
{
    startup_init();
    display_message("Paper Scissors Rock: First to 3");

    char stage = 'R';
    uint8_t p1_score = 0;
    uint8_t p2_score = 0;

    while (1) {
        pacer_wait();
        tinygl_update();
        navswitch_update();

        switch (stage) {
            case 'P' :
                round_task(&stage);
                break;

            case 'R' : // Ready check
                ready_task(&stage);
                break;

            case 'W' : // Round was won
                display_message("Won round!");
                p1_score++;
                if (p1_score == MAX_SCORE) {
                    stage = 'Q';
                } else {
                    stage = 'R';
                }
                break;

            case 'L' : // Round was lost
                display_message("Lost round!");
                p2_score++;
                if (p2_score == MAX_SCORE) {
                    stage = 'Q';
                } else {
                    stage = 'R';
                }
                break;

            case 'D' : // Round was a draw
                display_message("Draw!");
                stage = 'R';
                break;
        }
        if (stage == 'Q') {
            break;
        }
    }
    tinygl_clear();
    tinygl_update();
}

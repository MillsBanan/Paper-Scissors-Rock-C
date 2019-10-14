/** @file   game.c
    @authors Evan Oijordsbakken, Ryan Miller
    @date   09 October 2019

    This file runs the main program of the PSR game
    for the UCFK for Assignment
*/
#include <stdio.h>
#include "system.h"
#include "pacer.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "navswitch.h"
#include "../fonts/font5x7_1.h"
#include "round.h"
#include "ready.h"
#include "messages.h"
#include "button.h"

#define PACER_RATE 2000
#define MESSAGE_RATE 25
#define MAX_SCORE 3

void startup_init(void)
{
    system_init();
    ir_uart_init ();
    button_init();
    pacer_init(PACER_RATE);
    tinygl_init(PACER_RATE);
    tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
}

int main(void)
{
    startup_init();

    uint16_t timing_multiplier = 10 * (PACER_RATE / MESSAGE_RATE);
    char stage = 'R';
    uint8_t p1_score = 0;
    uint8_t p2_score = 0;

    display_message_once("Paper Scissors Rock:    ", timing_multiplier);
    display_message_once(" First to 3!    ", timing_multiplier);
    display_message_once(" Ready?  ", timing_multiplier);

    while (1) {
        pacer_wait();
        tinygl_update();
        navswitch_update();
        button_update();

        if (button_down_p(0)) {
            char buffer[21];
            sprintf(buffer, "  Scores.. P1:%d P2:%d", p1_score, p2_score);
            display_scores(buffer);
        }
        if (stage == 'Q') { // Quit the game
            break;
        }

        switch (stage) {
            case 'P' :
                round_task(&stage);
                break;

            case 'R' : // Ready check
                ready_task(&stage);
                break;

            case 'W' : // Round was won
                display_message_once(" ... Round won!   ", timing_multiplier);
                p1_score++;
                if (p1_score == MAX_SCORE) {
                    stage = 'Q';
                } else {
                    stage = 'R';
                    display_message_once(" Ready?  ", timing_multiplier);
                }
                break;

            case 'L' : // Round was lost
                display_message_once(" ... Round lost!   ", timing_multiplier);
                p2_score++;
                if (p2_score == MAX_SCORE) {
                    stage = 'Q';
                } else {
                    stage = 'R';
                    display_message_once(" Ready?  ", timing_multiplier);
                }
                break;

            case 'D' : // Round was a draw
                display_message_once(" ... Draw!  ", timing_multiplier);
                stage = 'R';
                display_message_once(" Ready?  ", timing_multiplier);
                break;
        }
    }
    if (p1_score > p2_score) {
        display_message_once(" You won the game!   ", timing_multiplier);
    } else {
        display_message_once(" You lost the game!   ", timing_multiplier);
    }
    display_message_once(" Chur  ", timing_multiplier);
    tinygl_clear();
    tinygl_update();
}

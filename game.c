/** @file     game.c
    @authors  Evan Oijordsbakken, Ryan Miller
    @date     15 October 2019
    @brief    A simple paper scissors rock game for two players

*/


#include <stdio.h>
#include "system.h"
#include "ir_uart.h"
#include "button.h"
#include "navswitch.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "messages.h"
#include "ready.h"
#include "round.h"


#define PACER_RATE 2000
#define MESSAGE_RATE 25
#define MAX_SCORE 3


/** Initialises all of the peripherals required for the game */
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


/** Displays the startup messages to the player */
void start_screen(void)
{
    display_message_once(" Paper Scissors Rock:     ");

    char buffer[17]; // 17 is length of string below + 1 for null terminator
    sprintf(buffer, " First to %d!    ", MAX_SCORE);
    display_message_once(buffer);

    display_message_once(" Ready?  ");
}


/** Plays the game */
void game_task(void)
{
    char stage = 'R';
    uint8_t p1_score = 0;
    uint8_t p2_score = 0;

    while (1) {
        pacer_wait();
        tinygl_update();
        navswitch_update();
        button_update();

        if (button_down_p(0)) {
            char buffer[21]; // 21 is len of string below + 1 for null terminator
            sprintf(buffer, "  Scores.. P1:%d P2:%d", p1_score, p2_score);
            display_scores(buffer);
        }

        if (stage == 'Q') { // Quit the game
            break;
        }

        switch (stage) {
        case 'P': // Play a round
            round_task(&stage);
            break;

        case 'R': // Ready check
            ready_task(&stage);
            break;

        case 'W': // Round was won
            display_message_once(" ...  Round won!   ");
            p1_score++;
            if (p1_score == MAX_SCORE) {
                stage = 'Q';
            } else {
                stage = 'R';
                display_message_once(" Ready?  ");
            }
            break;

        case 'L': // Round was lost
            display_message_once(" ...  Round lost!   ");
            p2_score++;
            if (p2_score == MAX_SCORE) {
                stage = 'Q';
            } else {
                stage = 'R';
                display_message_once(" Ready?  ");
            }
            break;

        case 'D': // Round was a draw
            display_message_once(" ...  Draw!  ");
            stage = 'R';
            display_message_once(" Ready?  ");
            break;

        default:
            break;
        }
    }

    if (p1_score > p2_score) {
        display_message_once(" You won the game!   ");
    } else {
        display_message_once(" You lost the game!   ");
    }
}


int main(void)
{
    startup_init();
    start_screen();

    game_task();

    display_message_once(" Thanks for coming to my ted talk  ");
    tinygl_clear();
    tinygl_update();
}

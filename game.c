/** @file   game.c
    @authors Evan Oijordsbakken, Ryan Miller
    @date   09 October 2019

    This file runs the main program of the PSR game
    for the UCFK for Assignment
*/

#include "system.h"
#include "pacer.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "navswitch.h"
#include "../fonts/font5x7_1.h"
#include "round.h"
#include "ready.h"


#define PACER_RATE 800
#define MESSAGE_RATE 25
#define MAX_SCORE 3
void start_screen(void)
{
    tinygl_text("Paper Scissors Rock: First to 3");

    while (1) {
        pacer_wait();
        tinygl_update();
        navswitch_update();

        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            break;
        }
    }
}

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

void ready_task(char* stage)
{
    static char p1_ready = 'Y';
    static char p2_ready = 'N';
    static uint8_t sent_Y = 0;

    display_character(p1_ready);
    change_selection(&p1_ready);

    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        ir_uart_putc(p1_ready);
        if (p1_ready == 'Y') {
            sent_Y = 1;
        } else {
            sent_Y = 0;
        }
    }
    if (ir_uart_read_ready_p()) {
        p2_ready = ir_uart_getc();
    }
    if (sent_Y && p2_ready == 'Y') {
        p2_ready = 'N';
        sent_Y = 0;
        *stage = 'P';
    }
}

void change_selection(char* p1_ready)
{
    if (navswitch_push_event_p(NAVSWITCH_EAST) || navswitch_push_event_p(NAVSWITCH_WEST)) {
        if (*p1_ready == 'Y') {
            *p1_ready = 'N';
        } else {
            *p1_ready = 'Y';
        }
    }
}

int main(void)
{
    startup_init();
    start_screen();

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
                p1_score++;
                if (p1_score == MAX_SCORE) {
                    stage = 'Q';
                } else {
                    stage = 'R';
                }
                break;

            case 'L' : // Round was lost
                p2_score++;
                if (p2_score == MAX_SCORE) {
                    stage = 'Q';
                } else {
                    stage = 'R';
                }
                break;

            case 'D' : // Round was a draw
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
